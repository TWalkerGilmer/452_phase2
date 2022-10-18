#include <stdlib.h>
#include "phase2.h"
#include "phase1.h"

/**
 * Structs
*/
// typedef struct Message { // TODO do we have a message struct?
//     void * data[MAX_MESSAGE]; // TODO finish
// } Message;

typedef struct Slot {
    void * data[MAX_MESSAGE];
} Slot;

typedef struct MailBox {
    int id;
    int numSlots;
    int slotSize;
    int nextSlot;
} MailBox;

typedef struct PCB {
    int pid;
    int isRunnable;
    int isBlocked;
} PCB;

/**
 * Global Variables
*/
// what is this TODO
void (*systemCallVec[MAXSYSCALLS])(systemArgs * args);
// static array of mailboxes with capacity MAXMBOX:
MailBox * mailboxArray[MAXMBOX];
// static array of mail slots with space for MAXSLOTS elements:
    // slots are shared across mailboxes
Slot * slotArray[MAXSLOTS];
// a "shadow" process table
    // will include any mechanisms needed for blocking ?
PCB * shadowProcessTable[MAXPROC];
// mbox id counter
int currentMailboxID;


/**
 * Prints an error message and terminates the simulation.
*/
static void nullsys(systemArgs * args) {
    USLOSS_Console("Running nullsys()");
    USLOSS_Halt(1);
}

/**
 * Halts the program if the system is not in kernel mode.
*/
static void kernelModeCheck() {
    if ((USLOSS_PSR_CURRENT_MODE & USLOSS_PsrGet()) == 0) {
        USLOSS_Console("Called in user mode");
        USLOSS_Halt(1);
    }
}

/**
 * Disables interrupts?
 * is this necessary?
*/
//static void disableInterrupts() {
    // do we need this?
//}

/**
 * Initialize data structures
*/
void phase2_init() {
    // set all elements of systemCallVec[] to nullsys(), a function above
    kernelModeCheck();
    void (*nullsys_func_ptr)(systemArgs*);
    nullsys_func_ptr = &nullsys;
    for (int i = 0; i < MAXSYSCALLS; i++) {
        systemCallVec[i] = nullsys_func_ptr;
    }
    // initialize mailboxArray to null
    int i = 0;
    for (i = 0; i < MAXMBOX; i++) {
        mailboxArray[i] = NULL;
    }
    // initialize slotArray to null
    for (i = 0; i < MAXSLOTS; i++) {
        slotArray[i] = NULL;
    }
    // begin counting mailboxes
    currentMailboxID = 0;
}

/**
 * Creates a new Mailbox
 * Returns id of mailbox, or -1 if no more mailboxes, or -1 if invalid args
*/
int MboxCreate(int numSlots, int slotSize) {
    kernelModeCheck();
    if (numSlots < 0 || numSlots > MAXSLOTS 
            || slotSize < 0 || slotSize > MAX_MESSAGE) {
        return -1;
    }
    int i;
    for (i = 0; i < MAXMBOX; i++) {
        if (mailboxArray[i] == NULL) {
            break;
        }
    }
    if (i == MAXMBOX) {
        // mailboxArray is full
        return -1;
    }
    MailBox new_mailbox;
    new_mailbox.id = currentMailboxID++;
    new_mailbox.numSlots = numSlots;

    return new_mailbox.id;
}



// mark



/**
 * Destroys a mailbox
*/
int MboxRelease(int mailboxID) {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * Sends a message through a mailbox.
 * 
*/
int MboxSend(int mailboxID, void * message, int messageSize) {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * Waits to receive a message through a mailbox
*/
int MboxReceive(int mailboxID, void * message, int maxMessageSize) {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * Conditional Send; refuses to block
*/
int MboxCondSend(int mailboxID, void * message, int messageSize) {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * Conditional Receive; refuses to block
*/
int MboxCondReceive(int mailboxID, void * message, int maxMessageSize) {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * Waits for an interrupt
*/
int waitDevice(int type, int unit, int * status) {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * Called by phase1 from init
*/
void phase2_start_service_processes() {
    kernelModeCheck();
}

/**
 * called by sentinel() to check if there are any currently blocked processes
*/
int phase2_check_io() {
    kernelModeCheck();
    return -1; // placeholder
}

/**
 * called by phase1 from the Clock Interrupt
*/
void phase2_clockHandler() { // return type?
    kernelModeCheck();
    // keep track of how many clock interrupts have occurred,
    // and (conditionally) send a message of every 5th interrupt

}

// interrupt handlers for the disk and terminal devices
// void abc(int a, void * b)

// syscall handler mechanism
