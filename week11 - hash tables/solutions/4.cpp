#include <unordered_map>
#include <vector>
bool containsNearbyDuplicate(std::vector<int> &nums, int k)
{
    std::unordered_map<int, int> seen;

    for (int i = 0; i < nums.size(); i++)
    {
        int val = nums[i];
        if (seen.find(val) != seen.end() && i - seen[val] <= k)
        {
            return true;
        }
        seen[val] = i;
    }

    return false;
}
