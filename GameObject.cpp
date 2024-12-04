#include "GameObject.hpp";




GameObject::GameObject(vector<vector<float>> _vertexes, Position _position, Direction _direction, float _speed):vertexes(_vertexes),
    position(_position),direction(_direction), speed(_speed){}


vector<float>  GameObject::get_collision_normal_vector(GameObject other){

  //Return of null vector means no collision found
  vector<float> first = MTV(vertexes, other.vertexes);
  vector<float> second = MTV(other.vertexes, vertexes);
    if (get_vector_size(first) < get_vector_size(second)){
      return first;
    }else{
      return second;
    }
}

// vector<float> GameObject::get_collision_normal_vector(GameObject other) {
//     vector<float> collision = MTV(vertexes, other.vertexes);
    
//     // Add a small epsilon to avoid floating-point precision issues
//     const float EPSILON = 1e-5;
//     if (abs(collision[0]) > EPSILON || abs(collision[1]) > EPSILON) {
//         return collision;
//     }
    
//     return {0, 0};
// }


void GameObject::draw(ALLEGRO_COLOR color){

    //Use draw_polygon instead
    al_draw_filled_rectangle(position.x -20, position.y+10, position.x +20, position.y-10, color);

}

void GameObject::draw(ALLEGRO_BITMAP *bitmap){
    al_draw_bitmap(bitmap, position.x, position.y, 0);

}

void GameObject::set_direction(Direction _direction){
    direction = _direction;
}

void GameObject::move(){
    position.x += speed*direction.x;
    position.y += speed*direction.y;
    for(auto &vertex: vertexes){
      vertex[0] += speed*direction.x;
      vertex[1] += speed*direction.y;
    }
}

Direction GameObject::get_direction(){
    return direction;
}

  
Position GameObject::get_position(){
    return position;
}

void GameObject::draw_vertexes(){
    for(auto &vertex:vertexes){
      al_draw_filled_circle(vertex[0], vertex[1], 2, al_map_rgb(0,0,255));
    }
}



float GameObject::get_maximum(vector<float> values){
    float tmp = values[0];
    for(auto elem: values){
      if(elem > tmp){
        tmp = elem;
      }
    }
    return tmp;
}

float GameObject::get_minimum(vector<float> values){
    float tmp = values[0];
    for(auto elem: values){
      if(elem < tmp){
        tmp = elem;
      }
    }
    return tmp;
}

float GameObject::get_vector_size(vector<float> vector){
    return sqrt(pow(vector[0], 2) + pow(vector[1], 2));
  }


vector<float> GameObject::MTV(vector<vector<float>> this_vertexes, vector<vector<float>> other_vertexes){
    
    vector<vector<float>> translation_vectors;

    for(int i = 0; i < this_vertexes.size(); i++) {
        vector<float> vertex1 = this_vertexes[i];
        vector<float> vertex2 = this_vertexes[(i + 1) % this_vertexes.size()];

        vector<float> this_projections;
        vector<float> other_projections;

        vector<float> normal_axis = {vertex2[1] - vertex1[1], -(vertex2[0] - vertex1[0])};
        float length = get_vector_size(normal_axis);
        normal_axis[0] /= length;
        normal_axis[1] /= length;

        for(int j = 0; j < this_vertexes.size(); j++){
        this_projections.push_back((this_vertexes[j][0] * normal_axis[0] + this_vertexes[j][1] * normal_axis[1]));
        }

        for(int j = 0; j < other_vertexes.size();j++){
        other_projections.push_back((other_vertexes[j][0] * normal_axis[0] + other_vertexes[j][1] * normal_axis[1]));
        }

        float this_min = get_minimum(this_projections);
        float this_max = get_maximum(this_projections);
        float other_min = get_minimum(other_projections);
        float other_max = get_maximum(other_projections);

        if(this_max >= other_min && this_min <= other_max) {

        float overlap = std::min(this_max - other_min, other_max - this_min);
        translation_vectors.push_back({normal_axis[0] * overlap, normal_axis[1] * overlap});
    }else{
        return vector<float>{0,0};
    }
    }
        for(int i = 0; i <translation_vectors.size(); i++){
        float dot_product = direction.x * translation_vectors[i][0] + direction.y*translation_vectors[i][1];
        if(dot_product > 0){
          translation_vectors.erase(translation_vectors.begin() + i);
        }
        }

        vector<float> res = {translation_vectors[0][0], translation_vectors[0][1]};
        for(auto &vector:translation_vectors){ 

        float size = get_vector_size(vector);

        if (get_vector_size(res) > size && size != 0){
            res[0] = vector[0];
            res[1] = vector[1];
        }
        }

    return res;
}

// vector<float> GameObject::MTV(vector<vector<float>> this_vertexes, vector<vector<float>> other_vertexes) {
//     float smallest_overlap = std::numeric_limits<float>::max();
//     vector<float> smallest_translation = {0, 0};

//     // Check axes of both polygons
//     for (int polygon = 0; polygon < 2; polygon++) {
//         vector<vector<float>>& current_vertexes = (polygon == 0) ? this_vertexes : other_vertexes;
        
//         for (size_t i = 0; i < current_vertexes.size(); i++) {
//             // Compute normal axis (perpendicular to current edge)
//             vector<float> vertex1 = current_vertexes[i];
//             vector<float> vertex2 = current_vertexes[(i + 1) % current_vertexes.size()];
            
//             // Perpendicular normal axis (normalized)
//             vector<float> normal_axis = {
//                 vertex2[1] - vertex1[1], 
//                 -(vertex2[0] - vertex1[0])
//             };
            
//             float axis_length = sqrt(normal_axis[0]*normal_axis[0] + normal_axis[1]*normal_axis[1]);
//             if (axis_length == 0) continue;
            
//             normal_axis[0] /= axis_length;
//             normal_axis[1] /= axis_length;

//             // Project vertices
//             float this_min = std::numeric_limits<float>::max();
//             float this_max = std::numeric_limits<float>::lowest();
//             float other_min = std::numeric_limits<float>::max();
//             float other_max = std::numeric_limits<float>::lowest();

//             for (auto& vertex : this_vertexes) {
//                 float proj = vertex[0] * normal_axis[0] + vertex[1] * normal_axis[1];
//                 this_min = std::min(this_min, proj);
//                 this_max = std::max(this_max, proj);
//             }

//             for (auto& vertex : other_vertexes) {
//                 float proj = vertex[0] * normal_axis[0] + vertex[1] * normal_axis[1];
//                 other_min = std::min(other_min, proj);
//                 other_max = std::max(other_max, proj);
//             }

//             // Check for separation
//             if (this_max < other_min || this_min > other_max) {
//                 return {0, 0}; // No collision
//             }

//             // Compute overlap
//             float overlap = std::min(this_max - other_min, other_max - this_min);
            
//             // Track smallest translation
//             if (overlap < smallest_overlap) {
//                 smallest_overlap = overlap;
//                 smallest_translation = {
//                     normal_axis[0] * overlap, 
//                     normal_axis[1] * overlap
//                 };
//             }
//         }
//     }

//     return smallest_translation;
// }

