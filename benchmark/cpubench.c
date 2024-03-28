#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<pthread.h>

// Global variables
long loop_count, l_c, th_count; // Loop count, loop count per thread, number of threads
struct timeval t; // Structure for time measurement
double f_avg, i_avg; // Average FLOPS and IOPS

// Thread Structure for FLOPS
struct FLOPSThread
{
    int lc, th_counter; // Loop counter, thread counter
    float fa, fb, fc, fd; // Floating-point numbers
    pthread_t threads; // Thread ID
};

// Function to perform floating-point arithmetic operations
void *FLOPSOperation(void *data)
{
    struct FLOPSThread *th_data = (struct FLOPSThread *) data; // Casting thread data to the appropriate structure

    for(th_data->lc = 1; th_data->lc <= l_c; th_data->lc++)
    {
        // Perform floating-point arithmetic operations
        th_data->fb + th_data->fc;
        th_data->fa - th_data->fb;
        th_data->fa + th_data->fd;
        th_data->fa + th_data->fb;
        // Operations repeated for benchmarking
    }
}

// Function to benchmark FLOPS
void FLOPSBenchmark()
{
    long l, c, m;
    double fs_t, fe_t, ft_t;
    struct FLOPSThread ft[th_count]; // Array of thread structures

    // Initialize thread data
    for(l = 0; l < th_count; l++)
    {
        ft[l].lc = 1;
        ft[l].th_counter = 1;
        ft[l].fa = 0.02;
        ft[l].fb = 0.2;
        ft[l].fc = 0;
        ft[l].fd = 0;
    }

    gettimeofday(&t, NULL);
    fs_t = t.tv_sec + (t.tv_usec / 1000000.0); // Start time

    // Create threads for FLOPS computation
    for(c = 0; c < th_count; c++)
    {
        pthread_create(&ft[c].threads, NULL, &FLOPSOperation, (void *)&ft[c]);
    }
    // Join threads after computation
    for(m = 0; m < th_count; m++)
    {
        pthread_join(ft[m].threads, NULL);
    }

    gettimeofday(&t, NULL);
    fe_t = t.tv_sec + (t.tv_usec / 1000000.0); // End time
    ft_t = fe_t - fs_t; // Total time taken
    f_avg += (loop_count * 30) / (ft_t * 1000000000); // Compute average FLOPS
}

// Thread Structure for IOPS
struct IOPSThread
{
    int lc, th_counter; // Loop counter, thread counter
    int ia, ib, ic, id; // Integer numbers
    pthread_t threads; // Thread ID
};

// Function to perform integer arithmetic operations
void *IOPSOperation(void *data)
{
    struct IOPSThread *th_data = (struct IOPSThread *) data; // Casting thread data to the appropriate structure

    for(th_data->lc = 1; th_data->lc <= l_c; th_data->lc++)
    {
        // Perform integer arithmetic operations
        th_data->ib + th_data->ic;
        th_data->ia - th_data->ib;
        th_data->ia + th_data->id;
        th_data->ia + th_data->ib;
        // Operations repeated for benchmarking
    }
}

// Function to benchmark IOPS
void IOPSBenchmark()
{
    int k, v, n;
    double is_t, ie_t, it_t;
    struct IOPSThread it[th_count]; // Array of thread structures

    // Initialize thread data
    for(k = 0; k < th_count; k++)
    {
        it[k].lc = 1;
        it[k].th_counter = 1;
        it[k].ia = 1;
        it[k].ib = 2;
        it[k].ic = 0;
        it[k].id = 0;
    }

    gettimeofday(&t, NULL);
    is_t = t.tv_sec + (t.tv_usec / 1000000.0); // Start time

    // Create threads for IOPS computation
    for(v = 0; v < th_count; v++)
    {
        pthread_create(&it[v].threads, NULL, &IOPSOperation, (void *)&it[v]);
    }
    // Join threads after computation
    for(n = 0; n < th_count; n++)
    {
        pthread_join(it[n].threads, NULL);
    }
    
    gettimeofday(&t, NULL);
    ie_t = t.tv_sec + (t.tv_usec / 1000000.0); // End time
    it_t = ie_t - is_t; // Total time taken
    i_avg += (loop_count * 30) / (it_t * 1000000000); // Compute average IOPS
}

int main(int argc, char *argv[])
{
    // Input validation
    if (argc < 3){
        printf("Incorrect number of parameters. Correct usage is mentioned below.\n");
        printf("./[objectname] [operation count] [thread count]\n");
        exit(1);
    }
    
    // Get input values
    loop_count = atoi(argv[1]); // loop count
    th_count = atoi(argv[2]); // thread count
    l_c = loop_count / th_count; // Sharing the operations across the threads
    f_avg = 0;
    i_avg = 0;

    printf("\nStarting CPU Benchmark...\n");
    printf("\nThreads Implemented: %ld \n", th_count);
    
    // FLOPs Benchmark
    printf("\nComputing CPU-FLOPs Performance...\n");
    for(int h = 1; h <= 5; h++)
    {
        FLOPSBenchmark();
    }
    printf("Number of FLOPs: %lf G-FLOPs\n", f_avg / 5);
    sleep(2);

    // IOPs Benchmark
    printf("\nComputing CPU-IOPs Performance...\n");
    for(int h = 1; h <= 5; h++)
    {
        IOPSBenchmark();
    }
    printf("Number of IOPs: %lf G-FLOPs\n", i_avg / 5);
    printf("\nEnding...\n");

    return 0;
}
