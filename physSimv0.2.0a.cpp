/*
Physics Simulator

An attempt to make some kind of basic physics simulator

Versions:
   Last Modified: 2019-01-24
      Aaron Woodhouse, ID: 100699990

   0.1.0a - 2019-01-10
      -Added basic projectile motion in 2D
      -Graphing of simulation
      -Collisions not implemented
      Aaron Woodhouse, ID: 100699990

   0.2.0a - 2019-01-24
      -changed graph visuals
      -added ground level visual
      Aaron Woodhouse, ID: 100699990

Authors:
   Aaron Woodhouse, ID: 100699990
*/
#include <iostream>
//#include <math.h>
//#include <algorithm>
/*
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <typeinfo>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <array>
*/

/*
// Notes //
// To Add //
-user can input data manually
-user can add events at times (like change in a) / can interrupt mid sim
-make 3D / 2D option
-add collisions
-optimize
-add physics modes
-github
*/

using namespace std;

float FG; // m/s^2
int FRAMES; // seconds (subject to change)
int FPS;
// FRAMES / FPS = total sim time

// x, y, vx, vy, ax, ay, t, M, px, py,       // kinetic energy
// 0, 1,  2,  3,  4,  5, 6, 7,  8,  9,

int currentFrame = 0;
float t = 0;

int gridSizeX;
int gridSizeY;
int valuePerX;
int valuePerY;
int gL;

// Classes

// Function Declarations
float forces(float **frames);           // function name subject to change
void getGraphInput();

int main() {

   system("clear");

   cout << "Physics Simulator v0.2.0a" << endl
        << "Made by Aaron Woodhouse" << endl << endl;

   cout << "FRAMES / FPS = total sim time" << endl;

   cout << "FPS: ";
   cin >> FPS;

   cout << "Frames: ";  // CHANGE SO USER ADDS SIM TIME, AND INTERVALS?
   cin >> FRAMES;
   FRAMES++;

   getGraphInput();

   float **frames = new float *[FRAMES];

   for (int i = 0; i < FRAMES + 1; i++) {
      frames[i] = new float[9];
   }

   for (int i = 0; i < FRAMES; i++) { // set variables to zero
      frames[0][i] = 0;
   }

   ////////////////////////////////

   // Get initial variables
   int ans;
   cout << "Add groud level? (1/0) ";  // implement collision
   cin >> ans;
   if (ans == 1) {
      cout << "Ground Level: ";
      cin >> gL;
   }
   cout << "Gravity: ";
   cin >> FG;
   cout << "x: ";
   cin >> frames[0][0];
   cout << "y: ";
   cin >> frames[0][1];
   cout << "vx: ";
   cin >> frames[0][2];
   cout << "vy: ";
   cin >> frames[0][3];
   cout << "ax: ";
   cin >> frames[0][4];
   cout << "ay (without gravity): ";
   cin >> frames[0][5];
   frames[0][5] += FG;

   cout << "m: ";
   cin >> frames[0][7];

   ////////////////////////////////

   cout << endl << "Simulating..." << endl << endl;

   // simulate //
   // set times
   for (int i = 0; i < FRAMES; i++) {
      frames[i][6] = float(i) / float(FPS); // time elapsed
   }

   for (int i = 0; i < FRAMES - 1; i++) {
      forces(frames);
      currentFrame++;
   }

   for (int i = 0; i < FRAMES; i++) {  // display frame info
      cout << "CF: " << i << "/" << FRAMES - 1  << endl
           << "(" << frames[i][0] << ", "
           << frames[i][1] << ")" << endl
           << "vx = " << frames[i][2] << endl
           << "vy = " << frames[i][3] << endl
           << "ax = " << frames[i][4] << endl
           << "ay = " << frames[i][5] << endl
           << "m = " << frames[i][7] << endl
           << "px = " << frames[i][8] << endl
           << "py = " << frames[i][9] << endl
           << "t = " << frames[i][6]
           << endl << "--------" << endl;
     }

   // display sim

   char **grid = new char *[gridSizeX];

   for (int i = 0; i < gridSizeX + 1; i++) {
      grid[i] = new char[gridSizeY];
   }

   for (int i = 0; i < gridSizeX; i++) {     // empty
      for (int k = 0; k < gridSizeY; k++) {
         grid[i][k] = '-';
      }
   }

   for (int i = 0; i < gridSizeX; i++) {     // ground
      grid[i][gL] = '=';
   }

   for (int j = 0; j < FRAMES; j++) {     // trajectory
      if ((int(frames[j][0]) / valuePerX) <= (gridSizeX) && (int(frames[j][0]) / valuePerX) >= 0) {
         if ((int(frames[j][1]) / valuePerY) <= (gridSizeY) && (int(frames[j][1]) / valuePerY) >= 0) {
            int a = (int(frames[j][0]) / valuePerX);
            int b = (int(frames[j][1]) / valuePerY);
            grid[a][b] = '#';
         }
      }
   }

   for (int k = gridSizeY - 1; k >= 0; k--) {
      for (int i = 0; i < gridSizeX; i++) {

         cout << " " << grid[i][k];

      }
      cout << endl;
   }

   //delete frames; // not working, breaks at end

   cout << endl << endl << "Simulation Complete" << endl << endl;

   return 0;

}

// Function Definitions
void getGraphInput() {

   cout << "Grid Size X: ";
   cin >> gridSizeX;
   while (gridSizeX <= 0) {
      cout << "Must be more than 0 " << endl;
      cout << "Grid Size X: ";
      cin >> gridSizeX;
   }

   cout << "Grid Size Y: ";
   cin >> gridSizeY;
   while (gridSizeY <= 0) {
      cout << "Must be more than 0 " << endl;
      cout << "Grid Size Y: ";
      cin >> gridSizeY;
   }

   cout << "Graph interval x: ";
   cin >> valuePerX;
   while (valuePerX <= 0) {
      cout << "Must be more than 0 " << endl;
      cout << "Graph interval x: ";
      cin >> valuePerX;
   }

   cout << "Graph interval y: ";
   cin >> valuePerY;
   while (valuePerY <= 0) {
      cout << "Must be more than 0 " << endl;
      cout << "Graph interval y: ";
      cin >> valuePerY;
   }

}

float forces(float **frames) {

   // create object classes to store these in?
   // would allow for ease in making 2 objects at once

   float x1 = frames[currentFrame][0]; // make into function?
   float y1 = frames[currentFrame][1];
   float vx1 = frames[currentFrame][2];
   float vy1 = frames[currentFrame][3];
   float ax1 = frames[currentFrame][4];
   float ay1 = frames[currentFrame][5];
   float t1 = frames[currentFrame][6];
   float t2 = frames[currentFrame + 1][6];
   float m = frames[currentFrame][7];
   float px1 = frames[currentFrame][8];
   float py1 = frames[currentFrame][9];
   float x2, y2, vx2, vy2, ax2, ay2, px2, py2;
   float dt = t2 - t1;

   ////////////////////////////////

   float dx = (vx1*dt) + (0.5*ax1*(dt*dt));
   float dy = (vy1*dt) + (0.5*ay1*(dt*dt));

   x2 = x1 + dx;
   y2 = y1 + dy;
   vx2 = vx1 + (ax1*dt);
   vy2 = vy1 + (ay1*dt);
   ax2 = (vx2 - vx1) / dt;
   ay2 = (vy2 - vy1) / dt;
   px2 = m * vx2;
   py2 = m * vy2;

   ////////////////////////////////

   frames[currentFrame + 1][0] = x2; // make into function?
   frames[currentFrame + 1][1] = y2;   // maybe make into a vector?
   frames[currentFrame + 1][2] = vx2;
   frames[currentFrame + 1][3] = vy2;
   frames[currentFrame + 1][4] = ax2;
   frames[currentFrame + 1][5] = ay2;
   frames[currentFrame + 1][8] = px2;
   frames[currentFrame + 1][9] = py2;

}
