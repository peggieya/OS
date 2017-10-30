/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>


/*
 *
 * Constants
 *
 */

struct lock *NE;
struct lock *NW;
struct lock *SE;
struct lock *SW;

struct semaphore *sem;

/*
 * Number of cars created.
 */

#define NCARS 20


/*
 *
 * Function Definitions
 *
 */

static const char *directions[] = { "N", "E", "S", "W" };

static const char *msgs[] = {
        "approaching:",
        "region1:    ",
        "region2:    ",
        "region3:    ",
        "leaving:    "
};

/* use these constants for the first parameter of message */
enum { APPROACHING, REGION1, REGION2, REGION3, LEAVING };

static void
message(int msg_nr, int carnumber, int cardirection, int destdirection)
{
        kprintf("%s car = %2d, direction = %s, destination = %s\n",
                msgs[msg_nr], carnumber,
                directions[cardirection], directions[destdirection]);
}
 
/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

//{ "N", "E", "S", "W" };

static
void
gostraight(unsigned long cardirection,
           unsigned long carnumber)
{
int carDest;
carDest = cardirection + 2;
carDest %= 4;

    /*
     * Avoid unused variable warnings.
     */
    
    //(void) cardirection;
    //(void) carnumber;
    //acquire locks according to its path
    switch(cardirection)
    {
    case 0:
    //nw
    lock_acquire(NW);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(SW);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(NW);
    //sw
    message(LEAVING, carnumber, cardirection, carDest);
    lock_release(SW);
    break;
    case 1:
    //ne
    lock_acquire(NE);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(NW);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(NE);
    //nw
    message(LEAVING, carnumber, cardirection, carDest);
    lock_release(NW);
    break;
    case 2:
    //se
    lock_acquire(SE);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(NE);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(SE);
    //ne
    message(LEAVING, carnumber, cardirection, carDest);
    lock_release(NE);
    break;
    case 3:
    //sw
    lock_acquire(SW);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(SE);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(SW);
    //se
    message(LEAVING, carnumber, cardirection, carDest);
    lock_release(SE);
    break;
    
    default:
    panic("invild direction");
    break;
    }
        
}



/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
         unsigned long carnumber)
{
int carDest;
carDest = cardirection + 1;
carDest %= 4;
    /*
     * Avoid unused variable warnings.
     */
//(void) cardirection;
    //(void) carnumber;
    //acquire locks according to its path
    switch(cardirection)
    {
    case 0:
    //nw
    lock_acquire(NW);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(SW);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(NW);
    //sw
    lock_acquire(SE);
    message(REGION3, carnumber, cardirection, carDest);
    lock_release(SW);
    //se
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(SE);
break;
case 1:
//ne
    lock_acquire(NE);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(NW);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(NE);
//nw
lock_acquire(SW);
    message(REGION3, carnumber, cardirection, carDest);
    lock_release(NW);
//sw
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(SW);
break;
case 2:
//se
    lock_acquire(SE);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(NE);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(SE);
//ne
lock_acquire(NW);
    message(REGION3, carnumber, cardirection, carDest);
    lock_release(NE);
//nw
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(NW);
break;
case 3:
//sw
    lock_acquire(SW);
    message(REGION1, carnumber, cardirection, carDest);
    lock_acquire(SE);
    message(REGION2, carnumber, cardirection, carDest);
    lock_release(SW);
//se
lock_acquire(NE);
    message(REGION3, carnumber, cardirection, carDest);
    lock_release(SE);
//ne
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(NE);
break;
default:
panic("invild direction");
break;
    }
}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection,
          unsigned long carnumber)
{
int carDest;
carDest = cardirection + 3;
carDest %= 4;
    /*
* Avoid unused variable warnings.
     */
//(void) cardirection;
    //(void) carnumber;
//acquire locks according to its path
    switch(cardirection)
    {
    case 0:
    //nw
    lock_acquire(NW);
    message(REGION1, carnumber, cardirection, carDest);
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(NW);
break;
case 1:
//ne
    lock_acquire(NE);
    message(REGION1, carnumber, cardirection, carDest);
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(NE);
break;
case 2:
//se
    lock_acquire(SE);
    message(REGION1, carnumber, cardirection, carDest);
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(SE);
break;
case 3:
//sw
    lock_acquire(SW);
    message(REGION1, carnumber, cardirection, carDest);
message(LEAVING, carnumber, cardirection, carDest);
    lock_release(SW);
break;
default:
panic("invild direction");
break;
    }
}


/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */
 
static
void
approachintersection(void * unusedpointer,
                     unsigned long carnumber)
{
    int cardirection, destdirection;
    /*
     * Avoid unused variable and function warnings.
     */

    (void) unusedpointer;
    //(void) carnumber;
// (void) gostraight;
// (void) turnleft;
// (void) turnright;

    /*
     * cardirection is set randomly.
     */
/*
*1 = N
*2 = E
*3 = S
*4 = W
*/
    cardirection = random() % 4;
    //cardirection = 2; 
    
    
    // 0 = turn left
    // 1 = go straight
    // 2 = turn right
    destdirection = random() % 3;
   
    //destdirection = 0;
    
    // convert turn direction to desination direction
    int destCode;
    switch(destdirection)
    {
    case 0:
    destCode = cardirection + 1;
    destCode %= 4;
    break;
    case 1:
    destCode = cardirection + 2;
    destCode %= 4;
    break;
    case 2:
    destCode = cardirection + 3;
    destCode %= 4;
    break;
    default:
    panic("invild destination");
    break;
    }
    
    //print enter message
message(APPROACHING, carnumber, cardirection, destCode);
    P(sem);
    switch(destdirection)
    {
    case 0:
    turnleft(cardirection,carnumber);
    break;
    case 1:
    gostraight(cardirection,carnumber);
    break;
    case 2:
    turnright(cardirection,carnumber);
    break;
    default:
    panic("invild destination");
    break;
    }
    V(sem);
}


/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs,
           char ** args)
{
    int index, error;

    /*
     * Avoid unused variable warnings.
     */
    (void) nargs;
    (void) args;
NE = lock_create("1");
NW = lock_create("2");
SW = lock_create("3");
SE = lock_create("4");
sem = sem_create("sem", 3);
    /*
     * Start NCARS approachintersection() threads.
     */

    for (index = 0; index < NCARS; index++) {

        error = thread_fork("approachintersection thread",
                            NULL,
                            index,
                            approachintersection,
                            NULL
                            );

        /*
         * panic() on error.
         */

        if (error) {
                
            panic("approachintersection: thread_fork failed: %s\n",
                  strerror(error)
                  );
        }
    }

    return 0;
}

