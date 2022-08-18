#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#include "matrix.h"
#include "vector.h"

#define MAT_SIZE 4
#define STEPS 10000
#define CLAMP 1e9

#define _p(x) (1.0 / expl((number)x))

typedef Vector R;

// #include <matplot/matplot.h>

number random() { return (number)rand() / RAND_MAX; }

number clamp(number value, number magnitude) {
  if (value > magnitude) {
    return magnitude;
  }

  if (value < -magnitude) {
    value = -magnitude;
  }

  return value;
}

void simulate(std::string columns, std::vector<Matrix> animals, Matrix modalities) {
  std::cout << columns << "\n";

  Vector state(animals.size(), [] (int _) { return random(); });
  Matrix freq(animals.size(), [] (int j, int i) { return j != i ? 0 : _p(j); });

  for (int i = 0; i < STEPS; i++) {
    std::cout << state.join(",") << "\n";

    auto chance = random();
    int c = 0;

    for (int j = 1; j < animals.size(); j++) {
      c += chance < _p(j);
    }

    for (int j = c; j >= 0; j--) {
      Matrix noise(animals.size(), [] (int j, int i) { return j != i ? 0 : random(); });

      auto delta =
        noise.apply(
          modalities.apply(
            freq.apply(animals[c])))
        .apply(state);

      state = state - delta;

      state.init([&state] (int k) { return clamp(state[k], CLAMP); });
    }
  }
}

void INTJ() {
  // Ni/Te/Fi/Se

  // BSPC
  std::vector<Matrix> animals{
    //Blast: Ni => Te
    Matrix{
     R{1, -1, 0, 0},
     R{1, -1, 0, 0},
     R{0, 0, 1, 0},
     R{0, 0, 0, 1}
    },
    //Sleep: Ni => Fi
    Matrix{
     R{1, 0, -1, 0},
     R{0, 1, 0, 0},
     R{1, 0, -1, 0},
     R{0, 0, 0, 1}
    },
    //Play: Te => Se
    Matrix{
     R{1, 0, 0, 0},
     R{0, 1, 0, -1},
     R{0, 0, 1, 0},
     R{0, 1, 0, -1}
    },
    //Consume: Fi => Se
    Matrix{
     R{1, 0, 0, 0},
     R{0, 1, 0, 0},
     R{0, 0, 1, -1},
     R{0, 0, 1, -1}
    }
  };

  // Se-F, De-M (Fi-M => Se-F)
  Matrix modalities{
    R{1, 0, 0, 0},
    R{0, -1, 0, 0},
    R{0, 0, 1, 0},
    R{0, 0, 0, -1}
  };

  simulate("Ni,Te,Fi,Se", animals, modalities);
}

void ESTJ() {
  std::vector<Matrix> animals{
    Matrix{
     R{1, -1, 0, 0},
     R{1, -1, 0, 0},
     R{0, 0, 1, 0},
     R{0, 0, 0, 1}
    },
    Matrix{
     R{1, 0, -1, 0},
     R{0, 1, 0, 0},
     R{1, 0, -1, 0},
     R{0, 0, 0, 1}
    },
    Matrix{
     R{1, 0, 0, 0},
     R{0, 1, 0, 0},
     R{0, 0, 1, -1},
     R{0, 0, 1, -1}
    },
    Matrix{
     R{1, 0, 0, 0},
     R{0, 1, 0, -1},
     R{0, 0, 1, 0},
     R{0, 1, 0, -1}
    }
  };

  Matrix modalities{
    R{-1, 0, 0, 0},
    R{0, 1, 0, 0},
    R{0, 0, -1, 0},
    R{0, 0, 0, 1}
  };

  simulate("Te,Si,Ne,Fi", animals, modalities);
}

int main() {
  INTJ();

  return 0;
}
