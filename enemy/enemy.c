#include "enemy.h"
void initEntity(Entity* e, bonus* b) {
    // Initialize each field of the Entity structure
    // Example initialization values, you can adjust as needed
    e->pos1.x = 100;
    e->pos1.y = 350;
    e->pos1.w = 0;
    e->pos1.h = 0;

    e->pos2.x = 0;
    e->pos2.y = 0;
    e->pos2.w = 50;
    e->pos2.h = 50;

    e->imgnum=5;
    e->frame=0;

    e->hp = 1; // Example hp
    e->direction = 1; // Example direction 1:right -1:left
    e->lvl = 1; // Example level
    e->collision = 0; // Example collision
    e->state=5; //1:idel 2: attack 3:die 4:hit 5:run

    int i;
    char numbimg [100];
    //idel
    for (i=1;i<=5;i++)
    {
        sprintf(numbimg,"assets/enemy 1/idel/right/image%d.png",i);
        e->idel_r[i-1] = IMG_Load(numbimg);

        sprintf(numbimg,"assets/enemy 1/idel/left/image%d.png",i);
        e->idel_l[i-1] = IMG_Load(numbimg);
    }
    //attack
    for (i=1;i<=5;i++)
    {
        sprintf(numbimg,"assets/enemy 1/attack/right/image%d.png",i);
        e->attack_r[i-1] = IMG_Load(numbimg);

        sprintf(numbimg,"assets/enemy 1/attack/left/image%d.png",i);
        e->attack_l[i-1] = IMG_Load(numbimg);
    }
    //die
    for (i=1;i<=5;i++)
    {
        sprintf(numbimg,"assets/enemy 1/die/right/image%d.png",i);
        e->die_r[i-1] = IMG_Load(numbimg);

        sprintf(numbimg,"assets/enemy 1/die/left/image%d.png",i);
        e->die_l[i-1] = IMG_Load(numbimg);
    }
    //run
    for (i=1;i<=5;i++)
    {
        sprintf(numbimg,"assets/enemy 1/run/right/image%d.png",i);
        e->run_r[i-1] = IMG_Load(numbimg);

        sprintf(numbimg,"assets/enemy 1/run/left/image%d.png",i);
        e->run_l[i-1] = IMG_Load(numbimg);
    }

    
    /////////////////////******BONUS******///////////////////////
    b->bonus=100;
    b->collision=0;

    b->pos.x=400;
    b->pos.y=350;
    b->pos.w=0;
    b->pos.h=0;
    char numbimg2 [100];
    for (i=0;i<=9;i++)
    {
        sprintf(numbimg2,"/home/mahdi/Bureau/enemy/assets/coins/tile%d.png",i);
        b->rotation[i] = IMG_Load(numbimg2);
    }
    b->imgnumb=9;
    b->frameb=0;
}


void afficherEnnemi(Entity e,bonus b, SDL_Surface  * screen)
{
    // Load background image//
    SDL_Surface* image = IMG_Load("assets/background/g_bg_test.jpg");
    if (image == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }
   SDL_BlitSurface(image, NULL, screen, NULL);
   SDL_Flip(screen);
   int i=1;
    /////////////////////////////////*********loading the enemy*********///////////////////////////////////////
    SDL_Rect srcRect;
    srcRect.h=0;
    srcRect.w=0;
    srcRect.x=0;
    srcRect.y=350;
    SDL_Rect destRect;
    int k;
    switch (e.direction)
   {
   case 1:
    switch (e.state)
    {
    case 1: /////////**********************IDEL**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.idel_r[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 2://///////**********************ATTACK**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.attack_r[e.frame], NULL, screen, &e.pos1);
        break;
    case 3://///////**********************DIE**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.die_r[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 4://///////**********************HIT**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.hit_r[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 5://///////**********************RUN/movement**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.run_r[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 6:
        /* code */
        break;
    
    }
   break;
   
   case -1:
   switch (e.state)
    {
    case 1: /////////**********************IDEL**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.idel_l[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 2://///////**********************ATTACK**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.attack_l[e.frame], NULL, screen, &e.pos1);
        break;
    case 3://///////**********************DIE**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.die_l[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 4://///////**********************HIT**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.hit_l[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 5://///////**********************RUN/movement**********************/////////
           //SDL_Delay(100);
           SDL_BlitSurface(e.run_l[e.frame], NULL, screen, &e.pos1);
        break;
    
    case 6:
        /* code */
        break;
    
    }
   break;
   }

   SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &b.pos);
   b.pos.x-=50;
   SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &b.pos);
   b.pos.x-=50;
   SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &b.pos);
   b.pos.x-=50;
   SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &b.pos);
   b.pos.x-=50;
   SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &b.pos);
   b.pos.x-=50;
   SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &b.pos);
   /* SDL_BlitSurface(b.rotation[b.frameb], NULL, screen, &srcRect );
   if (collisionTri(b,destRect)) //money and player
    {
         b.pos.x=-500;
         b.pos.y=-500;
         b.pos.w=0;
         b.pos.h=0;
    }*/


}
int collisionTri( bonus b,  SDL_Rect pose)
{
    int x1;
    int y1;
    int r1;
    int H=b.rotation[1]->h;
    int W=b.rotation[1]->w;
    x1=b.pos.x+(W /2);
    y1=b.pos.y+(H /2);
    r1=sqrt(((W/2)*(W/2))+((H/2)*(H/2)));
    /*if (W<H)
    {
        r1=W/2;
    }
    else
    {
        r1=H/2;
    }*/
    int x2;
    int y2;
    int r2;
    x2=pose.x+(pose.w /2);
    y2=pose.y+(pose.h /2);
    r2=sqrt(((pose.w/2)*(pose.w/2))+((pose.h/2)*(pose.h/2)));
    int d1;
    d1=sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
    int d2;
    d2=r1+r2;
    if (d1<=d2)
    {
        return 1; //collision existe (player/bonus)
    }
    else
    {
        return 0; //collision n'existe pas (player/bonus)
    }

}
void move(Entity * e,bonus* b)
{
    int random;
    if (e->state==5){
    e->pos1.x += e->direction * 10;
    if (e->pos1.x < 0 || e->pos1.x >=550 ) {
        // Reverse direction if enemy reaches screen edge
        e->direction *= -1;
    }}
    random=rand();
    if (e->frame==1)
    {
    
    if(random%2==0)
    {
        e->direction*= -1;
    }
    
    }
    // Advance to the next frame

    e->frame =(e->frame + 1)% e->imgnum;
    b->frameb =(b->frameb + 1)% b->imgnumb;
}
int collisionBB( Entity e, SDL_Rect pose)
{
    if ((pose.x+pose.w<e.pos1.x)||(pose.x>e.pos1.x+e.pos1.w)||(pose.y+pose.h<e.pos1.y)||(pose.y>e.pos1.y>e.pos1.y+e.pos1.h))
    {
        return 0; //pas de collision (player/enemy)
    }
    else
    {
        return 1; //collision existe (player/enemy)
    }
}
void moveIA( Entity * e)
{

}