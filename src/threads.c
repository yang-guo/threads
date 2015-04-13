#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#include "threadpool.h"
#include "k.h"

//********************************
// async jobs
//********************************
#define NUMTHREADS 8
#define QUEUESIZE 1000

static threadpool_t *threadpool=NULL;static I mainloop_pipe[2];static K value_fn;
typedef struct{K job;K callback;K job_result;I free_pipe[2];} async_job;

static async_job* threads_create_job(K job,K callback){
	async_job* job_p=(async_job*)malloc(sizeof(async_job));job_p->job=job;
	job_p->callback=callback;if(pipe(job_p->free_pipe)==-1){};R job_p;}
static void threads_free_job(async_job* job){r0(job->job);r0(job->callback);free(job);job = NULL;}

static void threads_thread_callback(V* arg){
	C b;async_job* job=arg;K ret=dot(value_fn,job->job);K result=job->job_result=b9(3,ret);r0(ret);
	if(write(mainloop_pipe[1],&job,sizeof(async_job*))==-1){};if(read(job->free_pipe[0],&b,1)==-1){};r0(result);}

static K threads_q_callback(int fd) {
	C b;async_job* job;I rd=read(fd,&job,sizeof(async_job*));K deserialized=knk(1,d9(job->job_result));
	K retval=dot(job->callback,deserialized);if(write(job->free_pipe[1],&b,1)==-1){};
	threads_free_job(job);r0(deserialized);R retval;}

K threads_init(K x) {
	unsigned char bytes[]={0x01,0x00,0x00,0x00,0x0a,0x00,0x00,0x00,0x65,0x13};
	K s=ktn(KG,sizeof(bytes));memcpy(kG(s),bytes,sizeof(bytes));
	if(!okx(s))R krr("serialization");value_fn=d9(s);
	if(!(threadpool=threadpool_create(NUMTHREADS,QUEUESIZE,0)))R krr("threadpool");
	if(pipe(mainloop_pipe)==-1)R krr("pipe");sd1(mainloop_pipe[0],threads_q_callback);R(K)0;}

K threads_async(K x,K y) {
	async_job *job=threads_create_job(knk(1,r1(x)),r1(y));
	threadpool_add(threadpool,threads_thread_callback,(V*)job,0);R(K)0;}