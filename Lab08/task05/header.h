#define NOT_READY -1
#define FILLED 0 //when sender fill data
#define TAKEN 1 //when receiver take data
#define GO 2 //wjem semder keep sending
#define STOP 3 //when sender stop sending data

struct ints {
    int num1, num2;
};
struct Memory {
    int status;
    int gostop;
    struct ints nums;
};

