def query1():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    # second clause
    l2 = [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]
    ans = ''
    for v, s1 in l1:
        for s2, s3 in l2:
            # third clause
            if (s1, s3) in [('5', '6'), ('7', '8')]:
                continue
            # fourth clause
            if (s2, v) in [('4', 'w'), ('4', 'b'), ('4', 'e'), ('6', 'w'), ('6', 'e')]:
                continue
            ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ', '

    print(ans)


def query2():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    # second clause
    l2 = [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]
    ans = ''
    for v, s1 in l1:
        for s2, s3 in l2:
            # third clause
            if (s2, v) not in [('4', 'b'), ('4', 'e')]:
                continue
            # fourth clause
            if (s3, s1) in [('5', '6'), ('7', '8')]:
                continue
            ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ', '

    print(ans)


def query3():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    ans = ''
    for v, s1 in l1:
        for s2 in range(1, 9):  # consider all possible stmt values, then filter later
            s2 = str(s2)
            # second clause
            if (s1, s2) in [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]:
                continue
            # third clause
            if (s2, v) in [('1', 'x'), ('4', 'b'), ('5', 'b')]:
                continue
            ans += v + ' ' + s1 + ' ' + s2 + ', '

    print(ans)


def query4():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    ans = ''
    for v, s1 in l1:
        for s2 in range(1, 9):  # consider all possible stmt values, then filter later
            s2 = str(s2)
            # second clause
            if (s1, s2) in [('1', '2'), ('2', '3'), ('3', '4'), ('5', '6'), ('7', '8')]:
                continue
            ans += v + ' ' + s1 + ' ' + s2 + ', '

    print(ans)


def query5():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    # second clause
    l2 = [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]
    ans = ''
    for v, s1 in l1:
        for s2, s3 in l2:
            for s4 in range(1, 9):  # consider all possible stmt values, then filter later
                s4 = str(s4)
                # third clause
                if (s3, s4) in [('5', '6'), ('7', '8')]:
                    continue
                for s5 in range(1, 9):  # consider all possible stmt values, then filter later
                    s5 = str(s5)
                    # fourth clause
                    if (s1, s5) in [('1', '2'), ('2', '3'), ('3', '4'), ('5', '6'), ('7', '8')]:
                        continue
                    ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ' ' + s4 + ' ' + s5 + ', '

    print(ans)


def query6():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    ans = ''
    for v, s1 in l1:
        for s2 in range(1, 9):  # consider all possible stmt values, then filter later
            s2 = str(s2)
            # second clause
            if (s1, s2) in [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]:
                continue
            for s3 in range(1, 9):  # consider all possible stmt values, then filter later
                s3 = str(s3)
                # third clause
                if (s3, v) in [('1', 'x'), ('4', 'b'), ('5', 'b')]:
                    continue
                ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ', '

    print(ans)


def query7():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    # second clause
    l2 = [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]
    ans = ''
    for v, s1 in l1:
        for s2, s3 in l2:
            for s4 in range(1, 9):  # consider all possible stmt values, then filter later
                s4 = str(s4)
                # third clause
                if (s3, s4) in [('5', '6'), ('7', '8')]:
                    continue
                ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ' ' + s4 + ', '

    print(ans)


def query8():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    ans = ''
    for v, s1 in l1:
        for s2 in range(1, 9):  # consider all possible stmt values, then filter later
            s2 = str(s2)
            for s3 in range(1, 9):  # consider all possible stmt values, then filter later
                s3 = str(s3)
                # second clause
                if (s2, s3) in [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]:
                    continue
                ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ', '

    print(ans)


def query9():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    ans = ''
    for v, s1 in l1:
        for s2 in range(1, 9):  # consider all possible stmt values, then filter later
            s2 = str(s2)
            for s3 in range(1, 9):  # consider all possible stmt values, then filter later
                s3 = str(s3)
                # second clause
                if (s2, s3) in [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]:
                    continue
                for s4 in range(1, 9):  # consider all possible stmt values, then filter later
                    s4 = str(s4)
                    # third clause
                    if (s4, s2) in [('1', '2'), ('2', '3'), ('3', '4'), ('5', '6'), ('7', '8')]:
                        continue
                    ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ' ' + s4 + ', '

    print(ans)


def query10():
    # first clause
    l1 = [('x', '1'), ('a', '2'), ('k', '3'), ('b', '4'), ('c', '4'), ('d', '4'), ('b', '5'), ('c', '7'), ('d', '8'),
          ('c', '6'), ('d', '6')]
    # second clause
    l2 = [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]
    ans = ''
    for v, s1 in l1:
        for s2, s3 in l2:
            for s4 in range(1, 9):  # consider all possible stmt values, then filter later
                s4 = str(s4)
                for s5 in range(1, 9):  # consider all possible stmt values, then filter later
                    s5 = str(s5)
                    # third clause
                    if (s4, s5) in [('4', '5'), ('4', '6'), ('6', '7'), ('6', '8')]:
                        continue
                    ans += v + ' ' + s1 + ' ' + s2 + ' ' + s3 + ' ' + s4 + ' ' + s5 + ', '

    print(ans)
