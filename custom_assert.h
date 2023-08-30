#ifdef DEBUG
    #define assert(X)                                            \
        do                                                           \
        {                                                             \
            if (!(X))                                                  \
                assert(#X, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
        }                                                                \
        while(0)
#else
    #define assert(X)\
        do { (void)sizeof(cond); } while(0s)
#endif
