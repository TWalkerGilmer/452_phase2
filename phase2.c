#include <stdlib.h>
#include "phase2.h"
#include "phase1.h"

#define DEBUG 1

/**
 * Structs
*/
typedef struct Slot {
    void * data[MAX_MESSAGE];
} Slot;

typedef struct MailBox {
    int id;
    int numSlots;
    int slotSize;
} MailBox;

typedef struct PCB {
    int pid;
    int isBlocked;
} PCB;

/**
 * Global Variables
*/
void (*systemCallVec[MAXSYSCALLS])(systemArgs * args);
// static array of mailboxes with capacity MAXMBOX:
MailBox * mailboxArray[MAXMBOX];
// static array of mail slots with space for MAXSLOTS elements:
    // slots are shared across mailboxes
Slot * slotArray[MAXSLOTS];
// a "shadow" process table
    // will include any mechanisms needed for blocking TODO
PCB * shadowProcessTable[MAXPROC];

/**
 * Function Declarations
*/
static void syscallHandler(int what, void *argsIn);

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
 * Disable Interrupts
*/
static void disableInterrupts() {
    kernelModeCheck();
    USLOSS_PsrSet( USLOSS_PsrGet() & ~USLOSS_PSR_CURRENT_INT );
}

/**
 * Restores interrupts to previous state
*/
void restoreInterrupts() {
    // gets the previous interrupt value and right shifts
    int new_mask= (USLOSS_PsrGet() & USLOSS_PSR_PREV_INT) >> 2;
    USLOSS_PsrSet(USLOSS_PsrGet() | new_mask);
}

/**
 * Initialize data structures,
 * namely the global variables
*/
void phase2_init() {
    if (DEBUG)
        USLOSS_Console("init: DEBUG ENABLED\n");
    // set all elements of systemCallVec[] to nullsys(), a function above
    kernelModeCheck();
    disableInterrupts();
    // initialize systemCallVec
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
    // initialize shadoProcessTable
    for (i = 0; i < MAXPROC; i++) {
        shadowProcessTable[i] = NULL;
    }
    restoreInterrupts();
}

/**
 * Creates a new Mailbox
 * Returns id of mailbox, or -1 if no more mailboxes, or -1 if invalid args
*/
int MboxCreate(int numSlots, int slotSize) {
    if (DEBUG)
        USLOSS_Console("MboxCreate\n");
    kernelModeCheck();
    disableInterrupts();
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

    mailboxArray[i]->id = i;
    mailboxArray[i]->numSlots = numSlots;
    mailboxArray[i]->slotSize = slotSize;
    // USLOSS_Console("mailbox made - id: %d\n", new_mailbox->id);  // TODO re
    // TODO finish? (initialize other parts of mailbox)
    
    restoreInterrupts();
    if (DEBUG)
        USLOSS_Console("new mailbox id: %d\n", i);
    return mailboxArray[i]->id;
}

/**
 * Destroys a mailbox
 * If the mailbox is in use, returns -1,
 * otherwise returns 0
*/
int MboxRelease(int mailboxID) {
    if (DEBUG)
        USLOSS_Console("MboxRelease\n");
    kernelModeCheck();
    disableInterrupts();

    // TODO: check things,
    // return -1 if mbox in use

    // mbox with id == mailboxID gets set to null
    mailboxArray[mailboxID] = NULL;

    restoreInterrupts();
    return 0;
}

/**
 * Sends a message through a mailbox.
*/
int MboxSend(int mailboxID, void * message, int messageSize) {
    if (DEBUG)
        USLOSS_Console("MboxSend\n");
    kernelModeCheck();
    disableInterrupts();
    // if mailbox is full TODO

    // add message to mailbox
    restoreInterrupts();
    return -1; // TODO return value?
}

/**
 * Waits to receive a message through a mailbox
*/
int MboxReceive(int mailboxID, void * message, int maxMessageSize) {
    if (DEBUG)
        USLOSS_Console("MboxReceive\n");
    kernelModeCheck();
    disableInterrupts();

    restoreInterrupts();
    return -1; // placeholder
}

/**
 * Conditional Send; refuses to block
*/
int MboxCondSend(int mailboxID, void * message, int messageSize) {
    if (DEBUG)
        USLOSS_Console("MboxCondSend\n");
    kernelModeCheck();
    disableInterrupts();



    restoreInterrupts();
    return -1; // placeholder
}

/**
 * Conditional Receive; refuses to block
*/
int MboxCondReceive(int mailboxID, void * message, int maxMessageSize) {
    kernelModeCheck();
    disableInterrupts();

    restoreInterrupts();
    return -1; // placeholder
}

/**
 * Waits for an interrupt
*/
int waitDevice(int type, int unit, int * status) {
    kernelModeCheck();
    disableInterrupts();

    restoreInterrupts();
    return -1; // placeholder
}

/**
 * Called by phase1 from init
*/
void phase2_start_service_processes() {
    kernelModeCheck();
    disableInterrupts();

    restoreInterrupts();
}

/**
 * called by sentinel() to check if there are any currently blocked processes
*/
int phase2_check_io() {
    kernelModeCheck();
    disableInterrupts();

    restoreInterrupts();
    return -1; // placeholder
}

/**
 * called by phase1 from the Clock Interrupt
*/
void phase2_clockHandler() { // return type?
    kernelModeCheck();
    disableInterrupts();
    // keep track of how many clock interrupts have occurred,
    // and (conditionally) send a message of every 5th interrupt
    restoreInterrupts();
}

// interrupt handlers for the disk and terminal devices
// void abc(int a, void * b)

/**
 * Syscall Handler Mechanism
*/
static void syscallHandler(int what, void *argsIn) {
    systemArgs *args = (systemArgs*) argsIn;
    if (what != USLOSS_SYSCALL_INT) {
        USLOSS_Console("TODO placeholder error message");
        USLOSS_Halt(1);
    }

    // TODO: check args

    USLOSS_PsrSet(USLOSS_PsrGet() | USLOSS_PSR_CURRENT_INT);
    systemCallVec[args->number](args);
}
