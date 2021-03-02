#ifndef WIFI_HPP
#define WIFI_HPP

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <events/events.hpp>
#include <utilities/messages/messages.hpp>
#include <configuration/configuration.hpp>

const char *ssid = "ESP32";        // Enter SSID here
const char *password = "12345678"; //Enter Password here

WiFiServer server(80);

String page;

bool comAvailable = false;

bool isComAvailable() { return comAvailable; };

void createHTMLPage()
{
    page = "<!DOCTYPE html> <html>\n";
    page += "<head><meta charset=\"utf-8\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"><link rel=\"icon\" href=\"#\">\n";
    page += "<title>Robot WiFi Controller</title>\n";
    page += "<style>";
    page += "html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    page += "body { margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    page += "button { border: none;color: white;width: 165px;padding: 12px;margin: 12px;cursor: pointer;border-radius: 5px; }\n";
    page += "a {color: white;text-decoration: none;font-size: 22px;}\n";
    page += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    page += ".button-start {background-color: #00770c;}\n";
    page += ".button-terminate {background-color: #a70000;}\n";
    page += ".button-reset {background-color: #00770c;}\n";
    page += ".button-initial-move {background-color: #0b5873;}\n";
    page += ".button-search {background-color: #0b5873;}\n";
    page += "</style>\n";
    page += "</head>\n";
    page += "<body>\n";
    page += "<h1>Configurações do Robô - ESP32</h1>\n";
    page += "<h4>Emita eventos para a state machine</h4>\n";
    page += "<button class=\"button-start\"><a href=\"/start\">Start</a></button>";
    page += "<button class=\"button-terminate\"><a href=\"/terminate\">Terminate</a></button>";
    page += "<button class=\"button-reset\"><a href=\"/reset\">Reset</a></button>";
    page += "<h4>Configure a estratégia de movimento inicial</h4>\n";
    page += "<button class=\"button-initial-move\"><a href=\"/initial-move-none\">None</a></button>";
    page += "<button class=\"button-initial-move\"><a href=\"/initial-move-full-frente\">Full Frente</a></button>";
    page += "<h4>Configure a estratégia de busca</h4>\n";
    page += "<button class=\"button-search\"><a href=\"/search-none\">None</a></button>";
    page += "<button class=\"button-search\"><a href=\"/search-radar\">Radar</a></button>";
    page += "</body>\n";
    page += "</html>\n";
};

void initCommunications()
{
    WiFi.softAP(ssid, password);
    delay(100);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println(myIP);
    createHTMLPage();

    server.begin();
    Serial.println("HTTP server started");
};

void handle_Communications()
{
    WiFiClient client = server.available();
    if (client)             // if you get a client,
    {                            
        String currentLine;
        while (client.connected())
        {
            if (client.available())     // if there's bytes to read from the client,
            {                           
                char c = client.read(); // read a byte
                if (c == '\n')
                { // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0)
                    {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        // the content of the HTTP response follows the header:
                        client.print(page);

                        // The HTTP response ends with another blank line:
                        client.println();
                        // break out of the while loop:
                        break;
                    }
                    else
                    { // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {                     // if you got anything else but a carriage return character,
                    currentLine += c; // add it to the end of the currentLine
                }

                // Check to see if the client request was "GET /H" or "GET /L":
                if (currentLine.endsWith("GET /start"))
                {
                    addEventToQueue(Event::Start);
                }
                if (currentLine.endsWith("GET /terminate"))
                {
                    addEventToQueue(Event::Terminate);
                }
                if (currentLine.endsWith("GET /reset"))
                {
                    addEventToQueue(Event::Reset);
                }
                if (currentLine.endsWith("GET /initial-move-none"))
                {
                    config.initialMove = InitialMove::none;
                    display_message("INITIAL MOVE: NONE");
                }
                if (currentLine.endsWith("GET /initial-move-full-frente"))
                {
                    config.initialMove = InitialMove::full_frente;
                    display_message("INITIAL MOVE: FULL FRENTE");
                }
                if (currentLine.endsWith("GET /search-none"))
                {
                    config.search = Search::none;
                    display_message("SEARCH: NONE");
                }
                if (currentLine.endsWith("GET /search-radar"))
                {
                    config.search = Search::radar;
                    display_message("SEARCH: RADAR");
                }
            }
        }
        // close the connection:
        //client.stop();
    }
};

#endif