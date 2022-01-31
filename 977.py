import bisect

class Solution(object):
    def sortedSquares(self, nums):
        left = 0
        right = len(nums) - 1

        result = []
        while left <= right:
            left_num = nums[left]
            right_num = nums[right]
            if abs(left_num) > abs(right_num):
                result.append(left_num * left_num)
                left += 1
            else:
                result.append(right_num * right_num)
                right -= 1
        result.reverse()
        return result

solution = Solution()
print(solution.sortedSquares([-4, -1, 0, 3, 10]))
print(solution.sortedSquares([-7, -3, 2, 3, 11]))
