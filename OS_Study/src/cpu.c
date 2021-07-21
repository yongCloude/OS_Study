#include "cpu.h"

Cpu* g_cpu;

int init_cpu(Parser* parameters) {
    if ((g_cpu = (Cpu*)malloc(sizeof(Cpu))) < 0) {
        PRINT_ERROR("INIT_CPU: FAIL");
        return -1;
    }
    g_cpu->policy = parameters->policy;
    g_cpu->quantums = parameters->quantums;
    g_cpu->process_time = 0;
    g_cpu->running_process = NULL;
    g_cpu->schedule_cnt = 0;
    PRINT_MSG("INIT_CPU: OK");
    return 0;
}
void terminate_cpu() {
    free(g_cpu->quantums);
    free(g_cpu);
    PRINT_MSG("TERMINATE_CPU: OK");
}

bool is_cpu_busy() {
    return (g_cpu->running_process != NULL);
}

void schedule_cpu(Proc* process) {
    if (g_cpu->running_process) {
        PRINT_ERROR("CPU already busy");
        exit(-1);
    }
    else if ((g_cpu->policy == POLICY_MLFQ && get_current_time() % g_cpu->quantums[process->priority])
            || (g_cpu->policy != POLICY_MLFQ && get_current_time() % g_cpu->quantums[0])) { 
        PRINT_ERROR("This is not a schedule term");
        exit(-1);
    }
    else if (process == NULL) {
        PRINT_ERROR("There is no process to schedule");
        exit(-1);
    }
    INC_CNT(g_cpu->schedule_cnt);
    g_cpu->running_process = process;
}

bool run_cpu() {
    Proc* cur_process = g_cpu->running_process;
    if (cur_process) {
        INC_CNT(cur_process->process_time);
        INC_CNT(g_cpu->process_time);
    }
    return (cur_process && cur_process->process_time == cur_process->required_time);
}

Proc* unschedule_cpu() {
    if (g_cpu->running_process == NULL) {
        PRINT_ERROR("CPU has no process");
        exit(-1);
    }
    Proc* res = g_cpu->running_process;
    g_cpu->running_process = NULL;
    return res;
}
