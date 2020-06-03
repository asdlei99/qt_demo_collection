#include "power.h"

export template <class T> T power (T a, int exp) {
  T ans = a;
  while (--exp > 0) {
    ans *= a;
  }
  return (ans);
}
