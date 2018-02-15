final class UserSolution {
	
	static void mstrcpy(char dst[], char src[])
	{
		int c = 0;
		while ((dst[c] = src[c]) != 0) ++c;
	}
	
	static int mstrcmp(char str1[], char str2[])
	{
		int c = 0;
		while (str1[c] != 0 && str1[c] == str2[c]) ++c;
		return str1[c] - str2[c];
	}
	
	static Solution.INFO db[];
	int dbCnt;
	
	public void init()
    {
		db = new Solution.INFO[5000];
		for (int i = 0; i < db.length; i++) {
			db[i] = new Solution.INFO();
		}
    }
    
	public void addDB(Solution.INFO info)
    {	
		mstrcpy(db[dbCnt].first, info.first);
		mstrcpy(db[dbCnt].second, info.second);
		mstrcpy(db[dbCnt].third, info.third);
		mstrcpy(db[dbCnt].fourth, info.fourth);
		mstrcpy(db[dbCnt].fifth, info.fifth);
		dbCnt++;
	}

	public int newCompound(Solution.INFO info)
	{
		// if (12<34) return newCompoundBrute(info);
		return newCompoundOptimized(info);
	}
	public int newCompoundBrute(Solution.INFO info)
	{
		int maxSum = 0;
		for(int i = dbCnt; i-->0;){
			int maxCorr = 0;
			int corr,sum = 0;
			sum += (corr = Solution.calc_correlation(db[i].first, info.first));
			if (maxCorr < corr)
				maxCorr = corr;
			sum += (corr = Solution.calc_correlation(db[i].second, info.second));
			if (maxCorr < corr)
				maxCorr = corr;
			sum += (corr = Solution.calc_correlation(db[i].third, info.third));
			if (maxCorr < corr)
				maxCorr = corr;
			sum += (corr = Solution.calc_correlation(db[i].fourth, info.fourth));
			if (maxCorr < corr)
				maxCorr = corr;
			sum += (corr = Solution.calc_correlation(db[i].fifth, info.fifth));
			if (maxCorr < corr)
				maxCorr = corr;

			if (100 > maxCorr) continue;
			if (maxSum < sum)
				maxSum = sum;
		}
		return maxSum;
	}
	public int newCompoundOptimized(Solution.INFO info)
	{
		// do your magic here :p
		return 0;
	}
}