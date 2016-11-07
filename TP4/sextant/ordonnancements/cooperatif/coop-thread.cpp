/* Copyright (C) 2004,2005 David Decotigny

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.
*/


//#include <drivers/TP1-video.h>

//#include <hal/TP2-irq.h>

#include "coop-thread.h"


/**
 * The size of the stack of a kernel thread
 */
#define THREAD_KERNEL_STACK_SIZE (1024)

void sched_clk(int intid) {
   thread_yield();
}

/**
 * The identifier of the thread currently running on CPU.
 *
 * We only support a SINGLE processor, ie a SINGLE thread
 * running at any time in the system. This greatly simplifies the
 * implementation of the system, since we don't have to complicate
 * things in order to retrieve the identifier of the threads running
 * on the CPU. On multiprocessor systems the current_thread below is
 * an array indexed by the id of the CPU, so that the challenge is to
 * retrieve the identifier of the CPU. This is usually done based on
 * the stack address (Linux implementation) or on some form of TLS
 * ("Thread Local Storage": can be implemented by way of LDTs for the
 * processes, accessed through the fs or gs registers).
 */
static volatile struct thread *current_thread = NULL;


/*
 * The list of threads currently in the system.
 *
 * @note We could have used current_thread for that...
 */
//static struct sos_thread *thread_list = NULL;
#define MAX_THREAD 10

static struct thread thread_list[MAX_THREAD];

typedef struct {
  char stack[THREAD_KERNEL_STACK_SIZE];
} toto;

toto thread_stack[MAX_THREAD];

/**
 * The Cache of thread structures
 */
//static struct sos_kslab_cache *cache_thread;


struct thread *thread_get_current()
{
  (current_thread->state == THR_RUNNING);
  return (struct thread*)current_thread;
}


inline static sextant_ret_t _set_current(struct thread *thr)
{
  (thr->state == THR_READY);
  current_thread = thr;
  current_thread->state = THR_RUNNING;
  return SEXTANT_OK;
}


sextant_ret_t thread_subsystem_setup(vaddr_t init_thread_stack_base_addr,
				     size_t init_thread_stack_size)
{
  struct thread *myself;
  int i;

  for (i=0;i<MAX_THREAD;i++)
	thread_list[i].state = EMPTY;

  /* Allocate the cache of threads */
  /*cache_thread = sos_kmem_cache_create("thread",
				       sizeof(struct sos_thread),
				       2,
				       0,
				       SOS_KSLAB_CREATE_MAP
				       | SOS_KSLAB_CREATE_ZERO);
  if (! cache_thread)
    return -SOS_ENOMEM;*/

  /* Allocate a new thread structure for the current running thread */
  i=0;
  myself=NULL;

  while (myself==NULL && i < MAX_THREAD) {

    if (thread_list[i].state == EMPTY)
		 	myself = &(thread_list[i]);
    i++;
  }

 // myself = (struct sos_thread*) sos_kmem_cache_alloc(cache_thread,
//						     SOS_KSLAB_ALLOC_ATOMIC);
  if (! myself)
    return -1;

  /* Initialize the thread attributes */
//  strzcpy(myself->name, "[kinit]", SOS_THR_MAX_NAMELEN);
  myself->state           = THR_CREATED;
  myself->kernel_stack_base_addr = init_thread_stack_base_addr;
  myself->kernel_stack_size      = init_thread_stack_size;

  /* Do some stack poisoning on the bottom of the stack, if needed */
 /* sos_cpu_state_prepare_detect_kernel_stack_overflow(myself->cpu_state,
						     myself->kernel_stack_base_addr,
						     myself->kernel_stack_size);*/

  /* Add the thread in the global list */
//  list_singleton_named(thread_list, myself, gbl_prev, gbl_next);

  /* Ok, now pretend that the running thread is ourselves */
  myself->state = THR_READY;
  _set_current(myself);

  return SEXTANT_OK;
}


struct thread *create_kernel_thread(const char *name,kernel_thread_start_routine_t start_func,void *start_arg)
{
  __label__ undo_creation;
  ui32_t flags;
  int i;
  struct thread *new_thread;
  void *temp;

 // sos_x86_videomem_putchar(2,0,VIDEO_FG_YELLOW | VIDEO_BG_BLUE,'C');

  if (! start_func)
    return NULL;

  /* Allocate a new thread structure for the current running thread */

  i=0;
  new_thread=NULL;

  while (new_thread==NULL && i < MAX_THREAD) {

    if (thread_list[i].state == EMPTY)
		 	new_thread = &(thread_list[i]);
    else i++;
  }


 /* new_thread
    = (struct sos_thread*) sos_kmem_cache_alloc(cache_thread,
						SOS_KSLAB_ALLOC_ATOMIC);*/
  if (! new_thread)
    return NULL;

 // sos_x86_videomem_putchar(2,1,VIDEO_FG_YELLOW | VIDEO_BG_BLUE,'C');

  /* Initialize the thread attributes */
 // strzcpy(new_thread->name, ((name)?name:"[NONAME]"), SOS_THR_MAX_NAMELEN);
  new_thread->state    = THR_CREATED;

  /* Allocate the stack for the new thread */
  temp = (void *) thread_stack[i].stack;

  new_thread->kernel_stack_base_addr = (vaddr_t) temp;
  new_thread->kernel_stack_size      = THREAD_KERNEL_STACK_SIZE;
  if (! new_thread->kernel_stack_base_addr)
    goto undo_creation;

  /* Initialize the CPU context of the new thread */
  if (SEXTANT_OK
      != cpu_kstate_init(& new_thread->cpu_state,
			     (cpu_kstate_function_arg1_t*) start_func,
			     (ui32_t) start_arg,
			     new_thread->kernel_stack_base_addr,
			     new_thread->kernel_stack_size,
			     (cpu_kstate_function_arg1_t*) thread_exit,
			     (ui32_t) NULL))
    goto undo_creation;

  /* Add the thread in the global list */
 /* sos_disable_IRQs(flags);
  list_add_tail_named(thread_list, new_thread, gbl_prev, gbl_next);
  sos_restore_IRQs(flags);*/

  /* Mark the thread ready */
  if (SEXTANT_OK != sched_set_ready(new_thread))

    goto undo_creation;

  /* Normal non-erroneous end of function */
  return new_thread;

 undo_creation:
 // sos_x86_videomem_putchar(2,3,SOS_X86_VIDEO_FG_YELLOW | SOS_X86_VIDEO_BG_BLUE,'U');
 /* if (new_thread->kernel_stack_base_addr)
    sos_kfree((sos_vaddr_t) new_thread->kernel_stack_base_addr);
  sos_kmem_cache_free((sos_vaddr_t) new_thread);*/
  new_thread->state = EMPTY;

  return NULL;
}


/** Function called after thr has terminated. Called from inside the context
    of another thread, interrupts disabled */
static void delete_thread(struct thread *thr)
{
  ui32_t flags;

 /* sos_disable_IRQs(flags);
  list_delete_named(thread_list, thr, gbl_prev, gbl_next);
  sos_restore_IRQs(flags);

  sos_kfree((sos_vaddr_t) thr->kernel_stack_base_addr);
  memset(thr, 0x0, sizeof(struct sos_thread));
  sos_kmem_cache_free((sos_vaddr_t) thr);*/

  int i;
  i=0;

  //sos_x86_videomem_putchar(6,0,VIDEO_FG_YELLOW | VIDEO_BG_BLUE,'D');

}

//KERNEL_OBJ

void thread_exit()
{
  ui32_t flags;
  struct thread *myself, *next_thread;

  /* Interrupt handlers are NOT allowed to exit the current thread ! */
  // SOS_ASSERT_FATAL(! sos_servicing_irq());

  myself = thread_get_current();

  /* Refuse to end the current executing thread if it still holds a
     resource ! */
 /* SOS_ASSERT_FATAL(list_is_empty_named(myself->kwaitq_list,
				       prev_entry_for_thread,
				       next_entry_for_thread));*/

  /* Prepare to run the next thread */
 // sos_disable_IRQs(flags);
  myself->state = THR_ZOMBIE;
  next_thread = reschedule(myself, false);

  /* Make sure that the next_thread is valid */
  /*sos_cpu_state_detect_kernel_stack_overflow(next_thread->cpu_state,
					     next_thread->kernel_stack_base_addr,
					     next_thread->kernel_stack_size);*/

  /* No need for sos_restore_IRQs() here because the IRQ flag will be
     restored to that of the next thread upon context switch */

  /* Immediate switch to next thread */
  _set_current(next_thread);
  cpu_context_exit_to(next_thread->cpu_state,
			  (cpu_kstate_function_arg1_t*) delete_thread,
			  (ui32_t) myself);
}


thread_state_t thread_get_state(struct thread *thr)
{
  if (! thr)
    thr = (struct thread*)current_thread;

  return thr->state;
}


typedef enum { YIELD_MYSELF, BLOCK_MYSELF } switch_type_t;
/**
 * Helper function to initiate a context switch in case the current
 * thread becomes blocked, waiting for a timeout, or calls yield.
 */
static sextant_ret_t _switch_to_next_thread(switch_type_t operation)
{
  struct thread *myself, *next_thread;

  (current_thread->state == THR_RUNNING);

  /* Interrupt handlers are NOT allowed to block ! */
  // SOS_ASSERT_FATAL(! sos_servicing_irq());

  myself = (struct thread*)current_thread;

  /* Make sure that if we are to be marked "BLOCKED", we have any
     reason of effectively being blocked */
  if (BLOCK_MYSELF == operation)
    {
      myself->state = THR_BLOCKED;
    }

  /* Identify the next thread */
  next_thread = reschedule(myself,YIELD_MYSELF == operation);

  /* Avoid context switch if the context does not change */
  if (myself != next_thread)
    {
      /* Sanity checks for the next thread */
    /*  sos_cpu_state_detect_kernel_stack_overflow(next_thread->cpu_state,
						 next_thread->kernel_stack_base_addr,
						 next_thread->kernel_stack_size);*/


      /*
       * Actual CPU context switch
       */
      _set_current(next_thread);
      cpu_context_switch(& myself->cpu_state, next_thread->cpu_state);

      /* Back here ! */
   //   SOS_ASSERT_FATAL(current_thread == myself);
    //  SOS_ASSERT_FATAL(current_thread->state == SOS_THR_RUNNING);
    }
  else
    {
      /* No context switch but still update ID of current thread */
      _set_current(next_thread);
      return SEXTANT_MYSELF;
    }

  return SEXTANT_OK;
}


sextant_ret_t thread_yield()
{
  ui32_t flags;
  sextant_ret_t retval;

//  sos_disable_IRQs(flags);
  // sos_x86_videomem_putchar(3,0,SOS_X86_VIDEO_FG_YELLOW | SOS_X86_VIDEO_BG_BLUE,'U');

  retval = _switch_to_next_thread(YIELD_MYSELF);

 // sos_x86_videomem_putchar(3,0,SOS_X86_VIDEO_FG_YELLOW | SOS_X86_VIDEO_BG_BLUE,'U');

//  sos_restore_IRQs(flags);
  return retval;
}

