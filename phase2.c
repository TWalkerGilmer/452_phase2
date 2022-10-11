#include <stdlib.h>
#include <assert.h>
#include "phase2.h"
#include "phase1.h"

/*
 * all processes must be called from kernel mode, check
 */

// Structs:
// Mailbox
// Message?

// typedef struct MailBox {
// } MailBox;

//void * systemCallVec[MAXSYSCALLS];
//void (*systemCallVec[])(systemArgs *args);  ???

// static array of mailboxes[MAXMBOX]
// static array of mail slots with space for MAXSLOTS elements
    // each slot holds MAX_MESSAGE bytes
    // slots are shared across mailboxes
// a "shadow" process table

static void nullsys() {
    // print an error message and terminate the simulation
    assert(0);
}

void phase2_init() {
    // among other things, (maybe?)
    // set all elements of systemCallVec[] to nullsys(), a function above
    void (*nullsys_func_ptr)(void);
    nullsys_func_ptr = &nullsys;
    for (int i = 0; i < MAXSYSCALLS; i++) {
        systemCallVec[i] = nullsys_func_ptr;
    }
}

/**
 * Creates a new Mailbox
*/
int MboxCreate(int numSlots, int slotSize) {

    return 0; // placeholder
}

/**
 * Destroys a mailbox
*/
int MboxRelease(int mailboxID) {

    return 0; // placeholder
}

/**
 * Sends a message through a mailbox.
 * 
*/
int MboxSend(int mailboxID, void * message, int messageSize) {

    return 0; // placeholder
}

/**
 * Waits to receive a message through a mailbox
*/
int MboxReceive(int mailboxID, void * message, int maxMessageSize) {

    return 0; // placeholder
}

/**
 * Conditional Send; refuses to block
*/
int MboxCondSend(int mailboxID, void * message, int messageSize) {

    return 0; // placeholder
}

/**
 * Conditional Receive; refuses to block
*/
int MboxCondReceive(int mailboxID, void * message, int maxMessageSize) {

    return 0; // placeholder
}

/**
 * Waits for an interrupt
*/
int waitDevice(int type, int unit, int * status) {

    return 0; // placeholder
}

/**
 * Called by phase1 from init
*/
void phase2_start_service_processes() {

}

/**
 * called by sentinel() to check if there are any currently blocked processes
*/
int phase2_check_io() {

    return 0; // placeholder
}

/**
 * called by phase1 from the Clock Interrupt
*/
void phase2_clockHandler() { // return type?

    // keep track of how many clock interrupts have occurred,
    // and (conditionally) send a message of every 5th interrupt

}

// interrupt handlers for the disk and terminal devices
// void abc(int a, void * b)

// syscall handler mechanism
