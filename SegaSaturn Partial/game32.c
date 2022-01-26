//game32.c
#include <jo/jo.h>
#include "actor32.h"
#include "interactor.h"
#include "map32.h"


typedef struct{
	Actor32 actors[200];
	int cur_actor;
	int camera_x;
	int camera_y;
	Interactor interactors[100];
	Map32 maps[10];
	int cur_map;
	int max_interactor;
	int max_actor;
}Game32_2d; // for 2d 32bit video game.

Game32_2d game;


int abs(int i){
	int out =i;
	if(i<0)out*=-1;
	return out;}

void apply_gravity_actor(int id){
	if(game.actors[id].vspeed<game.actors[id].max_vspeed){
		game.actors[id].vspeed+=game.actors[id].gravity;}
}

void apply_speeds_actor(int id){
	game.actors[id].x+=game.actors[id].hspeed;
	game.actors[id].y+=game.actors[id].vspeed;}

void update_actor(int id){
	apply_speeds_actor(id);
	apply_gravity_actor(id);
}

void draw_actor(int id){
	int current = game.actors[id].current_sprite;
	// check if on screen
	if(abs(game.camera_x-game.actors[id].x)<300){
		if(game.actors[id].is_animated[current]){
			jo_sprite_draw3D_and_rotate2(jo_get_anim_sprite(game.actors[id].sprite_graphics[current]), game.actors[id].x, game.actors[id].y, 450, game.actors[id].angle);
		}else{
			jo_sprite_draw3D_and_rotate2(game.actors[id].sprite_graphics[current], game.actors[id].x, game.actors[id].y, 450, game.actors[id].angle);
		}
	}
}


bool isDead_actor(int id){
	if(game.actors[id].hp==0)return true;
	return false;}

void setVspeed_actor(int id, int v){
	game.actors[id].vspeed=v;}

void setHspeed_actor(int id, int h){
	game.actors[id].hspeed=h;}

void stopHspeed_actor(int id){
	game.actors[id].hspeed=0;}

void stopVspeed_actor(int id){
	game.actors[id].vspeed=0;}

void applyGravity_actor(int id){
	game.actors[id].y+=game.actors[id].gravity;}

void init_sprite_actor(int id, int sprite_id,char *folder, char *filename){
	game.actors[id].sprite_graphics[sprite_id]=jo_sprite_add_tga(folder, filename, JO_COLOR_Green);
	game.actors[id].is_animated[sprite_id]=false;}


void init_interactor(int id, int x, int y, int h, int w, int type, int state, int spawn_actor_type, int timer){
	game.interactors[id].x=x;
	game.interactors[id].y=y;
	game.interactors[id].w=w;
	game.interactors[id].h=h;

	game.interactors[id].type=type;
	game.interactors[id].state=state;
	game.interactors[id].spawn_actor_type=spawn_actor_type;
	game.interactors[id].timer=timer;
}
void init_actor(int id,int x, int y, int w, int h, int type, int state){
	game.actors[id].x=x;
	game.actors[id].y=y;
	game.actors[id].w=w;
	game.actors[id].h=h;
	game.actors[id].type=type;
	game.actors[id].state=state;}

void draw_map(int id){

	jo_map_draw(id,game.maps[id].start_x,game.maps[id].start_y);
}
void init_map(int id, char *folder, char *filename){
	game.maps[id].map_id=id;
	jo_sprite_add_image_pack("WALL", "WALL.TEX", JO_COLOR_Green);
	jo_map_load_from_file(game.maps[id].map_id, 500, folder, filename);
}

void camera_update(int id){
	game.camera_x=game.actors[id].x;
	game.camera_y=game.actors[id].y;
}
