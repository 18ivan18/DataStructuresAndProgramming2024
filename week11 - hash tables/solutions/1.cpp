#include <vector>
#include <unordered_map>

std::vector<int> twoSum(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> hash;
    for (int i = 0; i < nums.size(); ++i)
    {
        int complement = target - nums[i];
        if (hash.find(complement) != hash.end())
        {
            return {hash[complement], i};
        }
        hash[nums[i]] = i;
    }
    // Return an empty vector if no solution is found
    return {};
}