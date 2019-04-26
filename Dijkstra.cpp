vector<pair<int, int>> AC_fun::dijkstra(const int start, const int end)
{
	const int len = matrix_.size();

	vector<bool> visit(len, false);
	vector<pair<int, double>> info(len, pair<int, double>(start, MAX)); // pair<from, distance>

	info[start].second = 0;

	for (auto vex = 0; vex < len; vex++)
	{
		auto next_vex = -1;
		auto min_dis = MAX;
		for (auto i = 0; i < len; i++)
			if (!visit[i] && info[i].second < min_dis)
			{
				next_vex = i;
				min_dis = info[i].second;
			}

		visit[next_vex] = true;

		for (auto i = 0; i < len; i++)
			if (!visit[i] && info[next_vex].second + matrix_[next_vex][i] < info[i].second)
			{
				info[i].first = next_vex;
				info[i].second = info[next_vex].second + matrix_[next_vex][i];
			}
	}

	vector<pair<int, int>> ans;
	auto x = info[end].first;
	auto y = end;
	while (y != start)
	{
		ans.emplace_back(x, y);
		y = x;
		x = info[x].first;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}