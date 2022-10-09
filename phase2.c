#include <stdlib.h>
#include "phase2.h"
#include "phase1.h"

/*
 * all processes must be called from kernel mode, check
 */

// Structs:
// Mailbox
// Message?

// systemCallVec[]

// static array of mailboxes[MAXMBOX]
// static array of mail slots with space for MAXSLOTS elements
    // each slot holds MAX_MESSAGE bytes
    // slots are shared across mailboxes
// a "shadow" process table

/**
 * Creates a new Mailbox
*/
int MboxCreate(int numSlots, int slotSize) {

}

/**
 * Destroys a mailbox
*/
int MboxRelease(int mailboxID) {

}

/**
 * Sends a message through a mailbox.
 * 
*/
int MboxSend(int mailboxID, void * message, int messageSize) {

}

/**
 * Waits to receive a message through a mailbox
*/
int MboxReceive(int mailboxID, void * message, int maxMessageSize) {

}

/**
 * Conditional Send; refuses to block
*/
int MboxCondSend(int mailboxID, void * message, int messageSize) {

}

/**
 * Conditional Receive; refuses to block
*/
int MboxCondReceive(int mailboxID, void * message, int maxMessageSize) {

}

/**
 * Waits for an interrupt
*/
int waitDevice(int type, int unit, int * status) {

}

/**
 * Called by phase1 from init
*/
void phase2_start_service_processes() {

}

/**
 * called by sentinel() to check if there are any currently blocked processes
*/
void phase2_check_io() {

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
