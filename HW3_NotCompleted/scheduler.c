#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "src/host.h"
#include "src/cpu.h"
#include "src/parser.h"


/* g_cpu : cpu 전역 변수, g_host : host 전역 변수
//실제 사용할 때는 직접 접근하지 마세요 (혹시나 간단하게 디버깅 할 때 관련 변수 쓸까봐 놔둠) 
//제출할 때는 사용한 부분 다 지우고 제출하도록!
*/
extern Cpu* g_cpu; 
extern Host* g_host;

/*****************구현 시작*****************/

/* 구현에 필요한 추가적인 자료구조 구현할 경우에 여기에 추가 */ 


/* 구현에 필요한 추가적인 함수 필요한 경우 여기에 추가 */



/* 
// 각 scheduler 구현을 위해 필요한 구조체
// (각 구조체에 사용할 정보들을 각각 저장해서 쓰세요.)
*/
typedef struct FIFO {

} FIFO;

typedef struct SJF {

} SJF;

typedef struct RR {

} RR;

typedef struct MLFQ {

} MLFQ;

typedef struct GUARANTEE {

} GUARANTEE;


/* 
// 각 scheduler의 시뮬레이션 전 initial 작업을 처리하는 함수
// (initial 작업으로 필요한 행동을 하면 됨.)
*/
void init_FIFO(FIFO** sch_fifo, Parser* parser) {

}
void init_SJF(SJF** sch_sjf, Parser* parser) {

}
void init_RR(RR** sch_rr, Parser* parser) {

}
void init_MLFQ(MLFQ** sch_mlfq, Parser* parser) {

}
void init_GUARANTEE(GUARANTEE** sch_guarantee, Parser* parser) {

}


/* 
// 각 scheduler의 시뮬레이션 중 한 cycle마다 해야할 행동을 처리하는 함수
// (한 cycle마다 해야할 행동을 작성하면 됨.)
*/
void simulate_FIFO(Proc* next_process, FIFO* sch_fifo) {

}

void simulate_SJF(Proc* next_process, SJF* sch_sjf) {

}

void simulate_RR(Proc* next_process, RR* sch_rr) {

}

void simulate_MLFQ(Proc* next_process, MLFQ* sch_mlfq) {

}

void simulate_GUARANTEE(Proc* next_process, GUARANTEE* sch_guarantee) {

} 


/* 
// 각 scheduler의 시뮬레이션이 끝나고 해야할 행동을 처리하는 함수
// (시뮬레이션이 끝나고 해야할 행동을 작성하면 됨.)
*/
void terminate_FIFO(FIFO* sch_fifo) {

}
void terminate_SJF(SJF* sch_sjf) {

}
void terminate_RR(RR* sch_rr) {

}
void terminate_MLFQ(MLFQ* sch_mlfq) {

}
void terminate_GUARANTEE(GUARANTEE* sch_guaranteeo) {

}

/******************구현 끝******************/


void print_result();
void* init_scheduler(Parser* parser);
void terminate_scheduler(void* scheduler, SCHEDULING_POLICY policy);

int main(int argc, char* argv[]) {
    Parser parser;
    void* scheduler = NULL;
    /*parse and err check parameters*/
    
    printf("\n=============== Environment Setting ================\n");
    if (parse_parameters(&parser, argc, argv) == -1) 
        return 0;
    printf("=================================================\n");

    /* init host & cpu & scheduler*/
    printf("\n=============== Init Simulation ================\n");
    
    if (init_host(&parser) == -1)
        return 0;
    if (init_cpu(&parser) == -1)
        goto term_host;
    if ((scheduler = init_scheduler(&parser)) == NULL)
        goto term_cpu;
    printf("=================================================\n");

    /* start simulation */
    printf("\n=============== Start Simulation ================\n\n");
    while (is_simulation_on_going()) {

        /* simulate one cycle start*/
        Proc* next_process = create_if_next_process_available();

        switch (parser.policy) {
        case POLICY_FIFO:
            simulate_FIFO(next_process, (FIFO*)scheduler);
            break;
        case POLICY_SJF:
            simulate_SJF(next_process, (SJF*)scheduler);
            break;
        case POLICY_RR:
            simulate_RR(next_process, (RR*)scheduler);
            break;
        case POLICY_MLFQ:
            simulate_MLFQ(next_process, (MLFQ*)scheduler);
            break;
        case POLICY_GUARANTEE:
            simulate_GUARANTEE(next_process, (GUARANTEE*)scheduler);
            break;
        }
        /* simulate one cycle finish*/
        increase_current_time();
    }
    printf("=============== Finish Simulation ===============\n\n");
    
    print_result(); //print result

    /*terminate scheduler & cpu & host*/
    printf("\n============= Terminate Simulation ==============\n");
    terminate_scheduler(scheduler, parser.policy);
term_cpu:
    terminate_cpu();
term_host:
    terminate_host();
    printf("=================================================\n");

    return 0;
}

void* init_scheduler(Parser* parser) {
    void* sch;
    switch(parser->policy) {
        case POLICY_FIFO:
            if((sch = (void*)malloc(sizeof(FIFO))))
                init_FIFO((FIFO**)(&sch), parser);
            break;
        case POLICY_SJF:
            if((sch = (void*)malloc(sizeof(SJF))))
                init_SJF((SJF**)(&sch), parser);
            break;
        case POLICY_RR:
            if((sch = (void*)malloc(sizeof(RR))))
                init_RR((RR**)(&sch), parser);
            break;
        case POLICY_MLFQ:
            if((sch = (void*)malloc(sizeof(MLFQ))))
                init_MLFQ((MLFQ**)(&sch), parser);
            break;
        case POLICY_GUARANTEE:
            if((sch = (void*)malloc(sizeof(GUARANTEE))))
                init_GUARANTEE((GUARANTEE**)(&sch), parser);
            break;
    }
    if (sch)
        PRINT_MSG("INIT SCHEDULER: OK");
    else
        PRINT_MSG("INIT SCHEDULER: FAIL");
    return sch;
}

void terminate_scheduler(void* scheduler, SCHEDULING_POLICY policy) {
    switch(policy) {
        case POLICY_FIFO:
            terminate_FIFO((FIFO*)scheduler);
        break;
        case POLICY_SJF:
            terminate_SJF((SJF*)scheduler);
        break;
        case POLICY_RR:
            terminate_RR((RR*)scheduler);
        break;
        case POLICY_MLFQ:
            terminate_MLFQ((MLFQ*)scheduler);
        break;
        case POLICY_GUARANTEE:
            terminate_GUARANTEE((GUARANTEE*)scheduler);
        break;
    }
    free(scheduler);
    PRINT_MSG("TERMINATE SCHEDULER: OK");
}

void print_result() {
    char policies[5][10] = {"FIFO", "SJF", "RR", "MLFQ", "GUARANTEE"};
    printf("\n=============== Simulation Result ===============\n");
    printf("scheduling policy: %s\n", policies[g_cpu->policy]);
    printf("request process: %lld\t", g_host->request_cnt);
    printf("service process: %lld\n", g_host->service_cnt);
    printf("schedule count: %d\n", g_cpu->schedule_cnt);
    printf("total process time(cycle): %lld\n", get_current_time());
    printf("total cpu time(cycle): %lld\t", g_cpu->process_time);
    printf("total turnaround time(cycle): %lld\n", g_host->turnaround_time);
    printf("=================================================\n");
}