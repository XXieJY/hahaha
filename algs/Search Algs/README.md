二分搜索法+插入法

int left = 0, right = tmp.size();
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                if (tmp[mid] >= nums[i])
                {
                  right = mid;
                }
                else
                {
                  left = mid + 1;
                }
            }
            res[i] = right;
            tmp.insert(tmp.begin() + right, nums[i]);