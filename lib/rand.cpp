struct seedbyclock{
    seedbyclock(){
        srand(std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now().time_since_epoch()).count());
    }
} initseed;

