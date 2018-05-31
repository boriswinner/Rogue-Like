import random

with open ('output.txt','w') as fout:
    for i in range(23):
        for j in range(23):
            if (i % 2 == 0):
                if (j < i):
                    if (random.randint(1,7) > 6):
                        print('*', i, j, 0, 0, file=fout)
                    else:
                        print('&', i, j, 0, 0, file=fout)
                else:
                    print('*', i, j, 0, 0, file=fout)
            else:
                if (random.randint(1, 7) > 6):
                    print('&', i, j, 0, 0, file=fout)
                else:
                    print('*', i, j, 0, 0, file=fout)
