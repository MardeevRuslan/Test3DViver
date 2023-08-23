#include "../parser_coordinates.h"
#include "../s21_affine.h"
#include "../s21_matrix.h"
#include "../s21_obj.h"

int print_obj(object_t *o);
int print_matrix(matrix_t *m);
int print_float_arr(float *arr, int index);
int print_int_arr(unsigned int *arr, int index);

int main() {
  const char *filename = "../objs/cube.obj";
  object_t obj = {0};
  init_obj(&obj);
  obj_parse(filename, &obj);
  obj.Scale->values[1] = 3;
  obj.Rotate->values[2] = 2;
  matrix_t *a = get_affine(&obj);
  int indices_count = get_indices_count(&obj);
  unsigned int *indices =
      (unsigned int *)calloc(indices_count * 2, sizeof(int));
  get_indices(&obj, indices);
  free(indices);
  s21_remove_matrix(a);
  free(a);
  return 0;
}

int print_obj(object_t *o) {
  for (int i = 0; i < o->vertex_count; i += 1) {
    matrix_t m = o->vertexes[i];
    printf("v %f %f %f\n", m.matrix[0][0], m.matrix[1][0], m.matrix[2][0]);
  }
  for (int i = 0; i < o->polygon_count; i += 1) {
    printf("f ");
    for (unsigned int j = 0; j < o->polygons[i].vertex_count; j += 1) {
      printf("%d ", o->polygons[i].vertexes[j]);
    }
    printf("\n");
  }
  return 0;
}

int print_matrix(matrix_t *m) {
  for (int i = 0; i < m->rows; i += 1) {
    for (int j = 0; j < m->columns; j += 1) {
      printf("A[%d][%d]: %.7lf  ", i, j, m->matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int print_float_arr(float *arr, int index) {
  for (int i = 0; i < index; i += 3) {
    printf("%f %f %f \n", arr[i], arr[i + 1], arr[i + 2]);
  }
  return 0;
}

int print_int_arr(unsigned int *arr, int index) {
  for (int i = 0; i < index; i += 2) {
    printf("%d %d \n", arr[i], arr[i + 1]);
  }
  return 0;
}
