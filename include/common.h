#ifndef COMMON_H
#define COMMON_H
#ifdef NUMBER
#undef NUMBER
#endif
#define NUMBER float

#ifdef PERCENTAGE
#undef PERCENTAGE
#endif
#define PERCENTAGE NUMBER

#ifdef PROBABILITY
#undef PROBABILITY
#endif
#define PROBABILITY NUMBER

#ifdef DIFFCOLOR
#undef DIFFCOLOR
#endif
#define DIFFCOLOR 64

#ifdef COLOR
#undef COLOR
#endif
#define COLOR 255
#endif //COMMON_H
