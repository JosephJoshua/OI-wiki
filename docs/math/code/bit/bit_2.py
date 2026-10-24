# --8<-- [start:mul]
def mulPowerOfTwo(n, m):  # compute n*(2^m)
    return n << m


def divPowerOfTwo(n, m):  # compute n/(2^m)
    return n >> m


# --8<-- [end:mul]
# --8<-- [start:abs]
def Abs(n):
    return (n ^ (n >> 31)) - (n >> 31)
    """
    n>>31 gets the sign of n: if n is positive, n>>31 is 0; if n is negative, n>>31 is -1
    If n is positive, n^0=n and the number is unchanged; if n is negative we have n^(-1)
    We need the two's complement of n and -1, then XOR them,
    which negates n and gives the absolute value of n minus 1; subtracting -1 then gives the absolute value
    """


# --8<-- [end:abs]
# --8<-- [start:minmax]
# if a >= b, (a - b) >> 31 is 0; otherwise it is -1
def max(a, b):
    return b & ((a - b) >> 31) | a & (~(a - b) >> 31)


def min(a, b):
    return a & ((a - b) >> 31) | b & (~(a - b) >> 31)


# --8<-- [end:minmax]
# --8<-- [start:sgn]
# except when one of them is 0
def isSameSign(x, y):
    return (x ^ y) >= 0


# --8<-- [end:sgn]
# --8<-- [start:get_bit]
# get bit b of a; the lowest bit is numbered 0
def getBit(a, b):
    return (a >> b) & 1


# --8<-- [end:get_bit]
# --8<-- [start:unset_bit]
# set bit b of a to 0; the lowest bit is numbered 0
def unsetBit(a, b):
    return a & ~(1 << b)


# --8<-- [end:unset_bit]
# --8<-- [start:set_bit]
# set bit b of a to 1; the lowest bit is numbered 0
def setBit(a, b):
    return a | (1 << b)


# --8<-- [end:set_bit]
# --8<-- [start:flap_bit]
# flip bit b of a; the lowest bit is numbered 0
def flapBit(a, b):
    return a ^ (1 << b)


# --8<-- [end:flap_bit]


if __name__ == "__main__":
    a, b = map(int, input().split())

    for i in range(16):
        print(f"{mulPowerOfTwo(a, i)} {divPowerOfTwo(a, i)}")

    assert Abs(-a) == a
    assert Abs(a) == a

    assert max(a, b) == (a if a > b else b)
    assert min(a, b) == (a if a < b else b)

    print(int(isSameSign(a, b)))

    for i in range(32):
        print(f"{getBit(a, i)} {unsetBit(a, i)} {setBit(a, i)} {flapBit(a, i)}")
