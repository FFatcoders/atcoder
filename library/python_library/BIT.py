class BIT:
    '''
    BIT represents Binary Indexed Tree (Fenwick Tree).

    Binary Indexed Tree (BIT), also known as Fenwick Tree, is a data structure
    that efficiently maintains prefix sums in an array.

    Attributes:
    - size (int): The size of the Binary Indexed Tree.
    - bit (list): A list representing the Binary Indexed Tree, initialized with zeros.

    Methods:
    - __init__(self, N): Initializes the Binary Indexed Tree with a given size N+1.
    - sum(self, i): Computes the prefix sum up to the i-th index.
    - add(self, i, x): Adds a value x to the i-th index and updates the Binary Indexed Tree.

    Example:
    >>> fenwick_tree = BIT(5)
    >>> fenwick_tree.add(2, 3)
    >>> fenwick_tree.add(4, 5)
    >>> fenwick_tree.sum(3)
    3
    >>> fenwick_tree.sum(5)
    8
    '''
    # 長さN+1の配列を初期化
    def __init__(self, N):
        '''
        Initializes a Binary Indexed Tree with a given size N+1.

        Args:
        - N (int): The size of the Binary Indexed Tree.
        '''
        self.size = N
        self.bit = [0]*(N+1)

    # i番目までの和を求める
    def sum(self, i):
        '''
        Computes the prefix sum up to the i-th index.

        Args:
        - i (int): The index up to which the prefix sum is computed.

        Returns:
        - int: The prefix sum up to the i-th index.
        '''
        res = 0
        while i > 0:
            res += self.bit[i] # フェニック木のi番目の値を加算
            i -= -i & i # 最も右にある1の桁を0にする
        return res

    # i番目の値にxを足して更新する
    def add(self, i, x):
        '''
        Adds a value x to the i-th index and updates the Binary Indexed Tree.

        Args:
        - i (int): The index at which the value is added.
        - x (int): The value to be added.
        '''
        while i <= self.size:
            self.bit[i] += x # フェニック木のi番目にxを足して更新
            i += -i & i # 最も右にある1の桁に1を足す
