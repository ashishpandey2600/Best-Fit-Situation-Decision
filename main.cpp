#include<bits/stdc++.h>
#include <vector>
#include "road.h"
#include "vehicle.h"
using namespace std;
int SPEED_LIMIT = 10;
double TRAFFIC_DENSITY = 0.15;//Make inputs
int MAX_ACCEL = 2;//Make inputs
vector<int>LANE_SPEEDS = { 6,7,8,9 }; //Make inputs
vector<int>GOAL = { 300,0 }; //Make inputs

int FRAMES_PER_SECOND = 4;
int AMOUNT_OF_ROAD_VISIBLE = 40;




int main(){
    LANE_SPEEDS[0]=6;
  LANE_SPEEDS[1]=7;
  LANE_SPEEDS[2]=8;
  LANE_SPEEDS[3]=9;

  GOAL[0]=300;
  GOAL[1]=0;
  Road road = Road(SPEED_LIMIT, TRAFFIC_DENSITY, LANE_SPEEDS);

  road.update_width = AMOUNT_OF_ROAD_VISIBLE;

  road.populate_traffic();

  int goal_s = GOAL[0];
  int goal_lane = GOAL[1];

  // configuration data: speed limit, num_lanes, goal_s, goal_lane,
  //   and max_acceleration
  int num_lanes = LANE_SPEEDS.size();
  vector < int > ego_config;
  ego_config[0]= SPEED_LIMIT;
   ego_config[1]=num_lanes;
    ego_config[2]= goal_s;
     ego_config[3]= goal_lane;
      ego_config[4]=MAX_ACCEL;

  road.add_ego(2,0, ego_config);
  int timestep = 0;

  while (road.get_ego().s <= GOAL[0]) {
    ++timestep;
    if (timestep > 100) {
      break;
    }
    road.advance();
    road.display(timestep);
    //time.sleep(float(1.0) / FRAMES_PER_SECOND);
  }

  Vehicle ego = road.get_ego();
  if (ego.lane == GOAL[1]) {
    cout << "You got to the goal in " << timestep << " seconds!" << endl;
    if(timestep > 35) {
      cout << "But it took too long to reach the goal. Go faster!" << endl;
    }
  } else {
    cout << "You missed the goal. You are in lane " << ego.lane
         << " instead of " << GOAL[1] << "." << endl;
  }
}
