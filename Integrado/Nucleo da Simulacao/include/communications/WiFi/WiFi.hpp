#ifndef WIFI_HPP
#define WIFI_HPP

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <events/events.hpp>
#include <utilities/messages/messages.hpp>

const char *ssid = "ESP32";        // Enter SSID here
const char *password = "12345678"; //Enter Password here

WiFiServer server(80);

String page;

String parameter;

bool comAvailable = false;

bool isComAvailable() { return comAvailable; };

Events getParametersFromCom()
{
    if (parameter == "START")
    {
        return Events::Start;
    }
    if (parameter == "TERMINATE")
    {
        return Events::Terminate;
    }
    comAvailable = false;
};

void createHTMLPage()
{
    page = "<!DOCTYPE html> <html>\n";
    page += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    page += "<title>Robot WiFi Controller</title>\n";
    page += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    page += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    page += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    page += ".button-on {background-color: #3498db;}\n";
    page += ".button-on:active {background-color: #2980b9;}\n";
    page += ".button-off {background-color: #34495e;}\n";
    page += ".button-off:active {background-color: #2c3e50;}\n";
    page += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    page += "</style>\n";
    page += "</head>\n";
    page += "<body>\n";
    page += "<h1>Configure Robot Strategies</h1>\n";
    page += "<h4>Using Access Point(AP) Mode</h4>\n";
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
    if (client)
    {                            // if you get a client,
        String currentLine = ""; // make a String to hold incoming data from the client
        while (client.connected())
        { // loop while the client's connected
            if (client.available())
            {                           // if there's bytes to read from the client,
                char c = client.read(); // read a byte, then
                Serial.write(c);        // print it out the serial monitor
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
                if (currentLine.endsWith("GET /Start"))
                {
                    comAvailable = true;
                    parameter = "START";
                }
                if (currentLine.endsWith("GET /Terminate"))
                {
                    comAvailable = true;
                    parameter = "TERMINATE";
                }
            }
        }
        // close the connection:
        //client.stop();
    }
};

#endif