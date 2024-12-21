#include "GameOrchestra.hpp"

GameOrchestra::GameOrchestra(){
    init_bricks();
}


void GameOrchestra::check_collisions(){

    for (int i =0; i < Bricks.size(); i++){
      vector<float> collision = ball.get_collision_normal_vector(Bricks[i]);
      if (collision[0] != 0 || collision[1] != 0){

        Bricks.erase(Bricks.begin()+i);
        Direction direction = get_reflected_direction(ball.get_direction(), collision);
        ball.set_direction(direction);
      }
    }

    //Check collision with the plate


    vector<float> plate_collision = ball.get_collision_normal_vector(plate);
    if(plate_collision[0] != 0 && plate_collision[1] != 0){
      float alpha = 30 + 120*(1 - (plate.get_position().x/plate_width));
      ball.set_direction(Direction{1, tan(alpha)});
    }

    
    //Check collision with the wall

    check_collision_wall();
}

void GameOrchestra::draw(){
    plate.draw(al_load_bitmap("Plate.png"));
    ball.draw();
    for(auto &brick:Bricks){
      brick.draw(al_map_rgb(255,0,0));
    }
  }

void GameOrchestra::move_plate(bool direction){
    plate.move(direction);
  }

void GameOrchestra::move_ball(){
    ball.move();
  }

void GameOrchestra::draw_ball(){
    ball.draw_vertexes();
  }

void GameOrchestra::draw_plate(){
    plate.draw_vertexes();
  }

void GameOrchestra::draw_bricks(){
    for(auto& brick: Bricks){
      brick.draw_vertexes();
    }
  }


Direction GameOrchestra::get_reflected_direction(Direction init_direction ,vector<float> normal){
    float length = sqrt(pow(normal[0], 2) + pow(normal[1], 2));
    normal[0] /= length;
    normal[1] /= length;
    return Direction{init_direction.x - 2*(init_direction.x*normal[0] + init_direction.y*normal[1])*normal[0],  init_direction.y - 2*(init_direction.x*normal[0] + init_direction.y*normal[1])*normal[1]};
  }


void GameOrchestra::init_bricks(){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 14; j++){
      Position position;
      position.x = (float)(40 *j + 20  );
      position.y = (float)((50 * (i+1)));
      Brick brick{al_map_rgb(255,0,0), position, {0,0}, 0};
      Bricks.push_back(brick);
      }
    }

  }

void GameOrchestra::check_collision_wall(){
    Position ball_position = ball.get_position();

    if(ball_position.x -5 <0){
      ball.set_direction(get_reflected_direction(ball.get_direction(), {1,0}));
    }
    if(ball_position.x +5>560){
      ball.set_direction(get_reflected_direction(ball.get_direction(), {-1,0}));
    }
    if(ball_position.y + 5<0){
      ball.set_direction(get_reflected_direction(ball.get_direction(), {0,1}));
    }
    if(ball_position.y - 5>900){
      ball.set_direction(get_reflected_direction(ball.get_direction(), {0,-1}));
    }

  }