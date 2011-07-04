#ifndef FQUARTNION_H
#define FQUARTNION_H

typedef struct
{
	float w, x, y, z;
} quartnion_t;

void quartnion_normalize(void);
void quartnion_conjugate(void);

//Quartnion Math
void quartnion_add(quartnion_t q1, quartnion_t q2);
void quartnion_subtract(quartnion_t q1, quartnion_t q2);
void quartnion_multiply(quartnion_t q1, quartnion_t q2);
void quartnion_divide(quartnion_t q1, quartnion_t q2);



//Matrix Conversion
void quartnion_to_matrix3();
void quartnion_to_matrix4();

#endif