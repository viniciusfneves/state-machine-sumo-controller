/*
 * Copyright 1996-2019 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>

// time in [ms] of a simulation step
#define TIME_STEP 16

#define NB_SENSORS 1
#define NB_LINESENSORS 2
#define RANGE (1024 / 2)

// entree point of the controller
int main(int argc, char **argv) {
  // initialise the Webots API
  wb_robot_init();

  // internal variables
  int i;
  int counter = 0;
  int avoid_obstacle_counter = 0;
  double speed[2];
  double line_sensor[NB_LINESENSORS];
  double dist_sensor[NB_SENSORS];

  
  WbDeviceTag ls[NB_LINESENSORS];
  WbDeviceTag ds[NB_SENSORS];
  char line_name[] = "line0";
  char dist_name[] = "dist0";

  // initialise line sensors
  for (i = 0; i < NB_LINESENSORS; i++) {
    ls[i] = wb_robot_get_device(line_name); /* get a handler to the sensor */
    /* Perform distance measurements every TIME_STEP millisecond. */
    wb_distance_sensor_enable(ls[i], TIME_STEP);
    /* Increase the device name to "ir1", "ir2", etc. */
    line_name[4]++;
  }
  
    // initialise distance sensors
  for (i = 0; i < NB_SENSORS; i++) {
    ds[i] = wb_robot_get_device(dist_name); /* get a handler to the sensor */
    /* Perform distance measurements every TIME_STEP millisecond. */
    wb_distance_sensor_enable(ds[i], TIME_STEP);
    /* Increase the device name to "ir1", "ir2", etc. */
    dist_name[4]++;
  }
  
  // initialise motors
  WbDeviceTag wheels[2];
  char wheels_names[2][8] = {"wheel1", "wheel2"};
  for (i = 0; i < 2; i++) {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
    wb_motor_set_velocity(wheels[i], 0);
  }

  // feedback loop
  while (wb_robot_step(TIME_STEP) != -1) {
    // init speeds
    
    for (i = 0; i < NB_LINESENSORS; i++)
      line_sensor[i] = wb_distance_sensor_get_value(ls[i]);
     
    for (i = 0; i < NB_SENSORS; i++)
      dist_sensor[i] = wb_distance_sensor_get_value(ds[i]);
    
    printf("distance line 0 value = %f    \n", line_sensor[0]);
    printf("distance line 1 value = %f    \n", line_sensor[1]);
    printf("counter = %f    \n", counter);
    //printf("distance sensor 0 value = %f    \n", dist_sensor[0]);
    /*
    
    double left_speed = 1.0;
    double right_speed = 1.0;

    if (avoid_obstacle_nter--;
      left_speed = 1.0;counter > 0) {
      avoid_obstacle_cou
      right_speed = -1.0;
    } else {
      // read sensors outputs
      double ds_values[2];
      for (i = 0; i < 2; i++)
        ds_values[i] = wb_distance_sensor_get_value(ds[i]);

      // increase counter in case of obstacle
      if (ds_values[0] < 950.0 || ds_values[1] < 950.0)
        avoid_obstacle_counter = 100;
    }
    */
    
    if (line_sensor[0] == 0 ||  line_sensor[1] == 0){
      speed[0] = -100; speed[1] = -100;
      counter = 11;
    } else if (counter > 7){
      speed[0] = -100; speed[1] = -100;
      counter--;
    } else if (counter > 0){
      speed[0] = 80; speed[1] = -80;
      counter--;
    } else{
      speed[0] = 130; speed[1] = 130;
    }
    
    //speed[0] = 40; speed[1] = 40;

    // write actuators inputs
    wb_motor_set_velocity(wheels[0], speed[0]);
    wb_motor_set_velocity(wheels[1], speed[1]);
  }

  // cleanup the Webots API
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}
