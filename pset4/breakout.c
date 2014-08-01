//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

#define PADDLEWIDTH 60
#define PADDLEHEIGHT 10



// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void moveBall(GWindow window, GOval ball, double* pointer_x, double* pointer_y);
void updatePaddle(GWindow window, GRect paddle);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject object);
void gameOver(GWindow window);
void youWon(GWindow window);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
  
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks on top of the games window
    initBricks(window);

    // instantiate ball, centered in middle of window. what returns from function initball transfers to GOval ball
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    
    
    
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    double velocity_x = 2 * drand48();
    double velocity_y = 3.0;


    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        updatePaddle(window, paddle);
        moveBall(window, ball, &velocity_x, &velocity_y);
        GObject object = detectCollision(window, ball);
       
        if(object != NULL)
        {
            if(object == paddle)
            {   
                velocity_y = 0 - velocity_y;
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                velocity_y = 0 - velocity_y;
                removeGWindow(window, object);
                
                points = points + 1;
                updateScoreboard(window, label, points);
                bricks = bricks - 1;
                if(bricks == 0)
                {
                    velocity_x = 0;
                    velocity_y = 0;
                    setLocation(paddle, 185, 550);
                    youWon(window);
                    waitForClick();
                }
            }
        }
        pause(10);
        
        if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            
            lives = lives - 1;
            setLocation(ball, 190, 290);
            setLocation(paddle, 185, 550);
             if(lives == 0)
             {
                gameOver(window);
                
             }
             waitForClick();
        }     
               
    }


    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int x = 3;
    int y = 50;
    
    for(int row = 0; row < ROWS; row++)
    {
       for(int column = 0; column < COLS; column++)
       {
             GRect bricks = newGRect(x, y, 35, 10);
             setFilled(bricks, true);
             if(row == 0)
             {
                setColor(bricks, "RED");
             }
             else if(row == 1)
             {
                setColor(bricks, "ORANGE");
             }
             else if (row == 2)
             {
                setColor(bricks, "YELLOW");
             }
             else if(row == 3)
             {
                setColor(bricks, "GREEN");
             }
             else
             {
                setColor(bricks, "BLUE");
             }
             add(window, bricks);
             x = x + 40;
             
         
       }
       y = y + 15;
       x = 3;
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(190, 290, 20, 20);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
     GRect rect = newGRect(185, 550, 60, 10);
      setFilled(rect, true);
      setColor(rect, "BLACK");
      add(window, rect);
      
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
      double x, y;
      GLabel label = newGLabel("0");
      setFont(label, "SansSerif-42");
      setColor(label, "CCCCCC");
      x = 189;
      y = 270;
      setLocation(label, x, y);
      add(window, label);
    return label;
}

void updatePaddle(GWindow window, GRect paddle)
{

    GEvent event = getNextEvent(MOUSE_EVENT);

    if (event != NULL)
    {
        if (getEventType(event) == MOUSE_MOVED)
        {
            double x = getX(event) - PADDLEWIDTH / 2;
            double y = 550;
            if(x <= 0)
            {
                x = 0;
            }
            else if(x >= WIDTH - PADDLEWIDTH)
            {
                x = WIDTH - PADDLEWIDTH;
            }
            setLocation(paddle, x, y);
        }
    }

}



/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

void moveBall(GWindow window, GOval ball, double* pointer_x, double* pointer_y)
{
        move(ball, *pointer_x, *pointer_y);
     
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            *pointer_x = 0 - *pointer_x;
            
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            *pointer_x = 0 - *pointer_x;
        }
        
        //if
        //{
        //    *pointer_y = 0 - *pointer_y;
        //}
        if(getY(ball) <= 0)
        {
           *pointer_y = 0 - * pointer_y;
        }
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
     


    // no collision
    return NULL;    
}

void gameOver(GWindow window)
{
      double x, y;
      GLabel label = newGLabel("Game Over");
      setFont(label, "SansSerif-42");
      setColor(label, "BLACK");
      x = 75;
      y = 200;
      setLocation(label, x, y);
      add(window, label);
}

void youWon(GWindow window)
{
      double x, y;
      GLabel label = newGLabel("You Won!");
      setFont(label, "SansSerif-42");
      setColor(label, "BLACK");
      x = 75;
      y = 200;
      setLocation(label, x, y);
      add(window, label);
}

