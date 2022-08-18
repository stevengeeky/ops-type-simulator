const clamp = (n: number, magnitude = 1e9) => {
  if (n > magnitude) {
    return magnitude;
  }

  if (n < -magnitude) {
    return -magnitude;
  }

  return n;
};

const p2 = 0.5;
const p3 = 0.25;
const p4 = 0.06125;

enum Direction {
  left,
  top,
  right,
  bottom,
}

type Stack = {
  N: number;
  T: number;
  F: number;
  S: number;
};

const stepINTJ = (direction: Direction, stack: Stack): Stack => {
  if (direction === Direction.bottom) {
    const diff = stack.F - stack.S;

    return {
      N: stack.N,
      T: stack.T,
      F: clamp(stack.F + Math.random() * p3 * diff),
      S: clamp(stack.S - Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.right) {
    stack = stepINTJ(Direction.bottom, stack);
    const diff = stack.T - stack.S;

    return {
      N: stack.N,
      T: clamp(stack.T - Math.random() * p2 * diff),
      F: stack.F,
      S: clamp(stack.S - Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.left) {
    stack = stepINTJ(Direction.right, stack);
    const diff = stack.N - stack.F;

    return {
      N: clamp(stack.N + Math.random() * diff),
      T: stack.T,
      F: clamp(stack.F + Math.random() * p3 * diff),
      S: stack.S,
    };
  }

  stack = stepINTJ(Direction.left, stack);
  const diff = stack.N - stack.T;

  return {
    N: clamp(stack.N + Math.random() * diff),
    T: clamp(stack.T - Math.random() * p2 * diff),
    F: stack.F,
    S: stack.S,
  };
};

const calculateINTJ = () => {
  const steps: number[][] = [];
  let stack = stepINTJ(Direction.top, {
    F: Math.random(),
    S: Math.random(),
    N: Math.random(),
    T: Math.random(),
  });

  for (let i = 0; i < 1000000; i++) {
    const chance = Math.random();

    const direction =
      chance > p2
        ? Direction.top
        : chance > p3
        ? Direction.left
        : chance > p4
        ? Direction.right
        : Direction.bottom;

    steps.push([stack.N, stack.T, stack.F, stack.S]);

    stack = stepINTJ(direction, stack);
  }

  return steps;
};

const stepISFP = (direction: Direction, stack: Stack): Stack => {
  if (direction === Direction.top) {
    const diff = stack.N - stack.T;

    return {
      F: stack.F,
      S: stack.S,
      N: clamp(stack.N - Math.random() * p3 * diff),
      T: clamp(stack.T + Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.left) {
    stack = stepISFP(Direction.top, stack);
    const diff = stack.F - stack.N;

    return {
      F: clamp(stack.F - Math.random() * diff),
      S: stack.S,
      N: clamp(stack.N - Math.random() * p3 * diff),
      T: stack.T,
    };
  }

  if (direction === Direction.right) {
    stack = stepISFP(Direction.left, stack);
    const diff = stack.S - stack.T;

    return {
      F: stack.F,
      S: clamp(stack.S + Math.random() * p2 * diff),
      N: stack.N,
      T: clamp(stack.T + Math.random() * p4 * diff),
    };
  }

  stack = stepISFP(Direction.right, stack);
  const diff = stack.F - stack.S;

  return {
    F: clamp(stack.F - Math.random() * diff),
    S: clamp(stack.S + Math.random() * p2 * diff),
    N: stack.N,
    T: stack.T,
  };
};

const calculateISFP = () => {
  const steps: number[][] = [];
  let stack = stepISFP(Direction.bottom, {
    F: Math.random(),
    S: Math.random(),
    N: Math.random(),
    T: Math.random(),
  });

  for (let i = 0; i < 1000000; i++) {
    const chance = Math.random();

    const direction =
      chance > p2
        ? Direction.bottom
        : chance > p3
        ? Direction.right
        : chance > p4
        ? Direction.left
        : Direction.top;

    steps.push([stack.F, stack.S, stack.N, stack.T]);
    stack = stepISFP(direction, stack);
  }

  return steps;
};

const stepENFP = (direction: Direction, stack: Stack): Stack => {
  if (direction === Direction.left) {
    const diff = stack.F - stack.S;

    return {
      N: stack.N,
      F: clamp(stack.F + Math.random() * p2 * diff),
      T: stack.T,
      S: clamp(stack.S + Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.top) {
    stack = stepENFP(Direction.left, stack);
    const diff = stack.T - stack.S;

    return {
      N: stack.N,
      F: stack.F,
      T: clamp(stack.T - Math.random() * p3 * diff),
      S: clamp(stack.S + Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.right) {
    stack = stepENFP(Direction.top, stack);
    const diff = stack.N - stack.T;

    return {
      N: clamp(stack.N - Math.random() * diff),
      F: stack.F,
      T: clamp(stack.T - Math.random() * p3 * diff),
      S: stack.S,
    };
  }

  stack = stepENFP(Direction.right, stack);
  const diff = stack.N - stack.F;

  return {
    N: clamp(stack.N - Math.random() * diff),
    F: clamp(stack.F + Math.random() * p2 * diff),
    T: stack.T,
    S: stack.S,
  };
};

const calculateENFP = () => {
  const steps: number[][] = [];
  let stack = stepENFP(Direction.bottom, {
    F: Math.random(),
    S: Math.random(),
    N: Math.random(),
    T: Math.random(),
  });

  for (let i = 0; i < 10000000; i++) {
    const chance = Math.random();

    const direction =
      chance > p2
        ? Direction.bottom
        : chance > p3
        ? Direction.right
        : chance > p4
        ? Direction.top
        : Direction.left;

    steps.push([stack.N, stack.F, stack.T, stack.S]);
    stack = stepENFP(direction, stack);
  }

  return steps;
};

const stepESTJ = (direction: Direction, stack: Stack): Stack => {
  if (direction === Direction.bottom) {
    const diff = stack.N - stack.F;

    return {
      T: stack.T,
      S: stack.S,
      N: clamp(stack.N - Math.random() * p3 * diff),
      F: clamp(stack.F - Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.left) {
    stack = stepESTJ(Direction.bottom, stack);
    const diff = stack.S - stack.F;

    return {
      T: stack.T,
      S: clamp(stack.S + Math.random() * p2 * diff),
      N: stack.N,
      F: clamp(stack.F - Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.right) {
    stack = stepESTJ(Direction.left, stack);
    const diff = stack.T - stack.N;

    return {
      T: clamp(stack.T + Math.random() * diff),
      S: stack.S,
      N: clamp(stack.N - Math.random() * p3 * diff),
      F: stack.F,
    };
  }

  stack = stepESTJ(Direction.right, stack);
  const diff = stack.T - stack.S;

  return {
    T: clamp(stack.T + Math.random() * diff),
    S: clamp(stack.S + Math.random() * p2 * diff),
    N: stack.N,
    F: stack.F,
  };
};

const calculateESTJ = () => {
  const steps: number[][] = [];
  let stack = stepESTJ(Direction.top, {
    F: Math.random(),
    S: Math.random(),
    N: Math.random(),
    T: Math.random(),
  });

  for (let i = 0; i < 1000000; i++) {
    const chance = Math.random();

    const direction =
      chance > p2
        ? Direction.top
        : chance > p3
        ? Direction.right
        : chance > p4
        ? Direction.left
        : Direction.bottom;

    steps.push([stack.T, stack.S, stack.N, stack.F]);
    stack = stepESTJ(direction, stack);
  }

  return steps;
};

const stepESFJ = (direction: Direction, stack: Stack): Stack => {
  if (direction === Direction.bottom) {
    const diff = stack.N - stack.T;

    return {
      F: stack.F,
      S: stack.S,
      N: clamp(stack.N + Math.random() * p3 * diff),
      T: clamp(stack.T + Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.left) {
    stack = stepESFJ(Direction.bottom, stack);
    const diff = stack.S - stack.T;

    return {
      F: stack.F,
      S: clamp(stack.S - Math.random() * p2 * diff),
      N: stack.N,
      T: clamp(stack.T + Math.random() * p4 * diff),
    };
  }

  if (direction === Direction.right) {
    stack = stepESFJ(Direction.left, stack);
    const diff = stack.F - stack.N;

    return {
      F: clamp(stack.F - Math.random() * diff),
      S: stack.S,
      N: clamp(stack.N + Math.random() * p3 * diff),
      T: stack.T,
    };
  }

  stack = stepESFJ(Direction.right, stack);
  const diff = stack.F - stack.S;

  return {
    F: clamp(stack.F - Math.random() * diff),
    S: clamp(stack.S - Math.random() * p2 * diff),
    N: stack.N,
    T: stack.T,
  };
};

const calculateESFJ = () => {
  const steps: number[][] = [];
  let stack = stepESFJ(Direction.top, {
    F: Math.random(),
    S: Math.random(),
    N: Math.random(),
    T: Math.random(),
  });

  for (let i = 0; i < 1000000; i++) {
    const chance = Math.random();

    const direction =
      chance > p2
        ? Direction.top
        : chance > p3
        ? Direction.right
        : chance > p4
        ? Direction.left
        : Direction.bottom;

    steps.push([stack.T, stack.S, stack.N, stack.F]);
    stack = stepESFJ(direction, stack);
  }

  return steps;
};

console.log(
  calculateESTJ()
    .map((x) => x.join(','))
    .join('\n')
);
