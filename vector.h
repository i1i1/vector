#define VECTOR_CAPACITY 8

typedef
struct
{
	unsigned int size;
	unsigned int capacty;
	int *data;
} vector;

void
vector_init(vector *Vector);

int
vector_getvalue(vector *Vector, int index);

void
vector_setvalue(vector *Vector, int index, int value);

void
vector_append(vector *Vector, int value);

void
vector_free(vector *Vector);
