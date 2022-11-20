import argparse
import os
import numpy as np

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--len', type=int, default=128)
    parser.add_argument('--idx', type=int, default=0)
    
    args = parser.parse_args()
    
    arr = np.random.randint(0, 123123, size=(args.len,))
    
    arr = list(arr)
    in_path = os.path.join("testcase", f"in{args.idx}.txt")
    with open(in_path, 'w') as f:
        f.write(str(args.len) + '\n')
        f.write(' '.join(map(str, arr)) + '\n')
    
    out = sorted(arr)
    out_path = os.path.join("testcase", f"out{args.idx}.txt")
    with open(out_path, 'w') as f:
        f.write(' '.join(map(str, out)) + '\n')


if __name__ == '__main__':
    main()