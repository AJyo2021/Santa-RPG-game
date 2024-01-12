

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <stdbool.h>
//#include <iostream>
//#include <sstream>

#define MAX_BULLETS 1
#define MAX_ENEMY 100

typedef struct
{
  float x, y, dy;
  short life;
  char *name;
  int currentSprite, walking, facingLeft, shooting, visible;
  int alive;
  
  SDL_Texture *sheetTexture;
} Man;

typedef struct
{
  float ex, ey, edy, edx;
  int life;
  int currentSprite, walking, facingLeft, shooting, visible;
  int alive;

  SDL_Texture *enemyTexture;
} Enemy;


typedef struct
{
  float x, y, dx;
} Bullet;


SDL_Texture *bulletTexture;
SDL_Texture *backgroundTexture;
SDL_Texture *HelloTexture;
SDL_Texture *enemyTexture;
SDL_Texture *Message; 
SDL_Texture *heartTexture;
SDL_Texture *GameOverTexture;
Bullet *bullets[MAX_BULLETS] = { NULL };
Enemy *enemys[MAX_ENEMY] = {NULL};
Mix_Music *mus, *mus2 ;  // Background Music 
Mix_Chunk *wav , *wav2 ;  // For Sounds



//Enemy enemys;

int globalTime = 0;
int Score = 0;
int rhearts = 3;

void addBullet(float x, float y, float dx)
{
  int found = -1;
  for(int i = 0; i < MAX_BULLETS; i++)
  {
    if(bullets[i] == NULL)
    {
      found = i;
      break;
    }
  }
    
  if(found >= 0)
  {
    int i = found;
    bullets[i] = malloc(sizeof(Bullet));
    bullets[i]->x = x;
    bullets[i]->y = y;
    bullets[i]->dx = dx;    
  }
}

void removeBullet(int i)
{
  if(bullets[i])
  {
    free(bullets[i]);
    bullets[i] = NULL;
  }
}
void spawnEnemy(float x, float y, float dx, float dy){
  int found = -1;
  for(int i = 0; i < MAX_ENEMY; i++)
  {
    if(enemys[i] == NULL)
    {
      found = i;
      break;
    }
  }
    
  if(found >= 0){
  
    int i = found;
    enemys[i] = malloc(sizeof(Enemy));
    enemys[i]->ex = x;
    enemys[i]->ey = y;
    enemys[i]->edx = dx;
    enemys[i]->edy = dy;    
    enemys[i]->currentSprite = 1;
    enemys[i]->facingLeft = 1;  
    enemys[i]->alive = 1;
    enemys[i]->visible = 1;
    enemys[i]->walking = 1; 



  
  
  }

return;

}

int processEvents(SDL_Window *window, Man *man)
{
  SDL_Event event;
  int done = 0;

  while(SDL_PollEvent(&event))
  {
    spawnEnemy(rand()%8000+250, 120, 0, 0);

    switch(event.type)
    {
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
        }
      }
      break;
      case SDL_QUIT:
        //quit out of the game
        done = 1;
      break;
    }
  }
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(!man->shooting)
  {
    if(state[SDL_SCANCODE_LEFT])
    {
      man->x -= 3;
      man->walking = 1;
      man->facingLeft = 1;
    
      if(globalTime % 6 == 0)
      {
        man->currentSprite++;
        man->currentSprite %= 4;  
      }  
    }
    else if(state[SDL_SCANCODE_RIGHT])
    {
      man->x += 3;
      man->walking = 1;
      man->facingLeft = 0;
     
      if(globalTime % 6 == 0)
      {
        man->currentSprite++;
        man->currentSprite %= 4;  
      }  
    }
    else
    {
      man->walking = 0;
      man->currentSprite = 4;
    }
  }

  if(!man->walking)
  {
    if(state[SDL_SCANCODE_SPACE])// && !man->dy)
    {
      if(globalTime % 6 == 0)
      {
        if(man->currentSprite == 4)         
          man->currentSprite = 5;
        else
          man->currentSprite = 4;
          
        if(!man->facingLeft)
        {
          addBullet(man->x+35, man->y+20, 3); 
        }
        else
        {
          addBullet(man->x+5, man->y+20, -3);         
        }
      }
      Mix_PlayChannel(-1,wav,0);   
  
      man->shooting = 1;
    }
    else 
    {
      man->currentSprite = 4;  
      man->shooting = 0;
    }
  }
  
  if(state[SDL_SCANCODE_UP] && !man->dy)
  {
    man->dy = -8;
     /* enemy.ex = 250;
  	enemy.ey = 120;
  enemy.currentSprite = 4;
  enemy.facingLeft = 1;  
  enemy.alive = 1;
  enemy.visible = 1;
 */
  }
  if(state[SDL_SCANCODE_DOWN])
  {
    //man->y += 10;
   // spawnEnemy(rand()%2000+250, 120, 0);

  }
  if(state[SDL_SCANCODE_S])
  {
   rhearts=3; 
  }  
  return done;
}

void doRender(SDL_Renderer *renderer, Man *man)
{
  //set the drawing color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  
  //Clear the screen (to blue)
  SDL_RenderClear(renderer);
  
  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
 
  //SDL_RenderFillRect(renderer, &rect);
  SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

  //warrior
  if(man->visible)
  {
    SDL_Rect srcRect = { 40*man->currentSprite, 0, 40, 50 };  
    SDL_Rect rect = { man->x, man->y, 40, 50 };  
    SDL_RenderCopyEx(renderer, man->sheetTexture, &srcRect, &rect, 0, NULL, man->facingLeft);
  }

  //enemy
  for(int i = 0; i < MAX_ENEMY; i++) if(enemys[i] && enemys[i]->visible)
  {
    SDL_Rect eSrcRect = { 40*enemys[i]->currentSprite, 0, 40, 50 };  
    SDL_Rect eRect = { enemys[i]->ex, enemys[i]->ey, 40, 50 };  
    SDL_RenderCopyEx(renderer, enemyTexture, &eSrcRect, &eRect, 0, NULL, enemys[i]->facingLeft);
  }

  for(int i = 0; i < MAX_BULLETS; i++) if(bullets[i])
  {
    SDL_Rect rect = { bullets[i]->x, bullets[i]->y, 8, 8 };  
    SDL_RenderCopy(renderer, bulletTexture, NULL, &rect);
  }

  //Score

//TTF_Font* Sans = TTF_OpenFont("MavenPro-VariableFont_wght.ttf", 24); //this opens a font style and sets a size
 // if(Sans == NULL)
  //{
  //  printf("Cannot find Font\n");
   // return;
  //}

//SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
//char buffer[128];
//sprintf(buffer, "Punkte: %d", Score);

//SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, buffer, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

//Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

//SDL_Rect Message_rect; //create a rect
//Message_rect.x = 10;  //controls the rect's x coordinate 
//Message_rect.y = 0; // controls the rect's y coordinte
//Message_rect.w = 50; // controls the width of the rect
//Message_rect.h = 50; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

//SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Hearts
  for(int i = 0; i < rhearts; i++) 
  {
    int hx = i*25+120;
    SDL_Rect rect = { hx, 13, 20, 20 };  
    SDL_RenderCopy(renderer, heartTexture, NULL, &rect);
  }

  //GameOver
  if( rhearts < 1) 
  {
    SDL_Rect rect = { 100, 100, 100, 100 };  
    SDL_RenderCopy(renderer, GameOverTexture, NULL, &rect);
  }


//We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

void updateLogic(Man *man)
{
  man->y += man->dy;
  man->dy += 0.5;
  if(man->y > 120)
  {
    man->y = 120;
    man->dy = 0;
  }
	for(int j = 0; j < MAX_ENEMY; j++) if(enemys[j])
        { 
	 int jump = rand()%201/200;
	 if (jump == 1)
	 {
		 enemys[j]->edy += -8;
	 }
	 
         enemys[j]->ex -= (rand()%41/10);
	 enemys[j]->walking = 1;
         enemys[j]->facingLeft = 1;
	 enemys[j]->ey += enemys[j]->edy;
         enemys[j]->edy += 0.5;
         if(enemys[j]->ey > 120)
         {
           enemys[j]->ey = 120;
           enemys[j]->edy = 0;
         }


         if(globalTime % 6 == 0 && enemys[j]->currentSprite < 6)
         {
          enemys[j]->currentSprite++;
          enemys[j]->currentSprite %= 5;  
         }
	//detect enemy collision 
         if(man->x == enemys[j]->ex  && man->y == enemys[j]->ey )
	 {
           rhearts--;
	   Mix_PlayChannel(-1,wav2,0); 
	 }	 
	}
  
  
  
     for(int i = 0; i < MAX_BULLETS; i++) if(bullets[i])
     {

	     bullets[i]->x += bullets[i]->dx;
    
    //simple coll. detection

       for(int j = 0; j < MAX_ENEMY; j++) if(enemys[j] && enemys[j]->visible)
       {

  
        if(bullets[i]->x > enemys[j]->ex && bullets[i]->x < enemys[j]->ex+40 && 
         bullets[i]->y > enemys[j]->ey && bullets[i]->y < enemys[j]->ey+50)
        {
          enemys[j]->alive = 0;
	  Mix_PlayChannel(-1,wav2,0); 
	  bullets[i]->x = -2000;
	  
        }

       }	
    
    if(bullets[i]->x < 20 || bullets[i]->x > 300)
      removeBullet(i);
     }
     
  
  for(int j=0; j < MAX_ENEMY; j++) if(enemys[j])
  {	  
    if(enemys[j]->alive == 0 && globalTime % 6 == 0)
    {
	    enemys[j]->ey += -5;
	    if(enemys[j]->currentSprite == 7 && enemys[j]->visible == 1)
      {
	      enemys[j]->currentSprite = 7;
	       enemys[j]->ey += -10;
	       enemys[j]->visible = 0;
	       if(rhearts > 0) {Score += 1;}




      }

	    if(enemys[j]->currentSprite < 6)
      {
	      enemys[j]->currentSprite = 6;
	       enemys[j]->ey += -5;
      }
      else 
      {
	  enemys[j]->currentSprite = 7;	
	   enemys[j]->ey += -10;
      }

    }
  }
  
  globalTime++;
}
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* Hello = NULL; 

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
  Hello = IMG_Load( "title_screen.png" );
    if( Hello == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "title_screen.png", SDL_GetError() );
        success = false;
    }

    return success;
}

int main(int argc, char *argv[])
{
	//Initialize SDL_ttf
  //TTF_Init();

  SDL_Window *window;                    // Declare a window
  SDL_Renderer *renderer;                // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
 
  // Inilialize SDL_mixer , exit if fail
  SDL_Init(SDL_INIT_AUDIO);
  // Setup audio mode
  Mix_OpenAudio(22050,AUDIO_S16SYS,2,4096);
//  Mix_Music *mus, *mus2 ;  // Background Music 
//  Mix_Chunk *wav , *wav2 ;  // For Sounds
//  mus = Mix_LoadMUS("./mixer/ff2prlde.mid");
  if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
    printf("Mix_Init Error: %s\n", Mix_GetError());
    // Handle initialization error.
    }

  if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1) {
    printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
    // Handle audio initialization error.
  }
  mus2 = Mix_LoadMUS("Das_Zauberbuch.mp3");

  if (mus2 == NULL)
  {
    printf("Error loading mus2: %s\n", Mix_GetError());
	  return 1;
  }
  wav = Mix_LoadWAV("Snowball_throw.wav");
  wav2 = Mix_LoadWAV("Snowball_Splat.wav");
  Mix_PlayMusic(mus2,-1); //Music loop=0
//  while( Mix_PlayingMusic() == 1)
//  {
  // Do something
//  SDL_Delay(10);
//  }
Mix_FreeMusic(mus2);

  Man man;
  man.x = 50;
  man.y = 0;
  man.currentSprite = 4;  
  man.alive = 1;
  man.visible = 1;
  man.facingLeft = 0;
  
   //enemys.ex = 250;
  //enemys.ey = 120;
  //enemys.currentSprite = 4;
  //enemys.facingLeft = 1;  
  //enemys.alive = 1;
  //enemys.visible = 1;
  
  //Create an application window with the following settings:

  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640,                               // width, in pixels
                            480,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   SDL_RenderSetLogicalSize(renderer, 320, 240);

  //Loads media
  loadMedia();
  //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
	    return 1;
        }
        else
        {
   
	     //SDL_RenderTitle
	     // SDL_UpdateWindowSurface( window )
	     HelloTexture = SDL_CreateTextureFromSurface(renderer, Hello);

//SDL_RenderFillRect(renderer, &rect);
  	SDL_RenderCopy(renderer, HelloTexture, NULL, NULL);

	//We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);

	    //Wait two seconds
            SDL_Delay( 4000 );

           
	    
	            }

    
  SDL_Surface *sheet = IMG_Load("Santa_sheet.png");
  if(!sheet)
  {
    printf("Cannot find sheet\n");
    return 1;
  }
  
  man.sheetTexture = SDL_CreateTextureFromSurface(renderer, sheet);  
  SDL_FreeSurface(sheet);
  
  //load enemy
  SDL_Surface *esheet = IMG_Load("Krampus_sheet.png");
  if(!esheet)
  {
    printf("Cannot find sheet\n");
    return 1;
  }
  
  enemyTexture = SDL_CreateTextureFromSurface(renderer, esheet);  
  SDL_FreeSurface(esheet);  

  //load the bg  
  SDL_Surface *bg = IMG_Load("game_background.png");
  
  if(!bg)
  {
    printf("Cannot find background\n");
    return 1;
  }

  backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
  SDL_FreeSurface(bg);

    //load the heart  
  SDL_Surface *heart = IMG_Load("heart.png");
  
  if(!heart)
  {
    printf("Cannot find heart\n");
    return 1;
  }

  heartTexture = SDL_CreateTextureFromSurface(renderer, heart);
  SDL_FreeSurface(heart);

   //load  Game Over
  SDL_Surface *go = IMG_Load("GameOver.png");
  
  if(!go)
  {
    printf("Cannot find GO\n");
    return 1;
  }

  GameOverTexture = SDL_CreateTextureFromSurface(renderer, go);
  SDL_FreeSurface(go);

  //load the bullet  
  SDL_Surface *bullet = IMG_Load("Snowball.png");
  
  if(!bullet)
  {
    printf("Cannot find bullet\n");
    return 1;
  }

  bulletTexture = SDL_CreateTextureFromSurface(renderer, bullet);
  SDL_FreeSurface(bullet);
  
  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
 
  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &man);
    
     //spawnEne'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''my(250, 120, 0);

    //Update logic
    updateLogic(&man);


    //Render display
    doRender(renderer, &man);
    
    //don't burn up the CPU
    SDL_Delay(10);
  }
  
  
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(man.sheetTexture);
  SDL_DestroyTexture(backgroundTexture);
  SDL_DestroyTexture(bulletTexture);
  SDL_DestroyTexture(enemyTexture);
  SDL_DestroyTexture(GameOverTexture);
  SDL_DestroyTexture(Message);
  Mix_FreeMusic(mus2);
  Mix_FreeChunk(wav);
  Mix_FreeChunk(wav2);
  
  for(int i = 0; i < MAX_BULLETS; i++)
    removeBullet(i);
  
  // Clean up
  //TTF_Quit();
  Mix_CloseAudio();
  Mix_Quit();
  SDL_Quit();
  return 0;
}

