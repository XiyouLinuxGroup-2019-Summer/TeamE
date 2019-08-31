#ifndef TABENN1_H_
#define TABENN1_H_
#include<string>

using std::string;

class TableTennisPlayer
{
	private:
		string firstname;
		string lastname;
		bool hasTAble;
	public:
		TableTennisPlayer(const string &fn = "none",const string &ln = "node",bool ht = false);
		void Name() const;
		bool HasTable() const { return hasTAble; };
		void ResetTable(bool v) { hasTAble = v; };
};

class RatePlayer : public TableTennisPlayer
{
	private:
		unsigned int rating;
	public:
		RatePlayer(unsigned int r = 0,const string &fn = "none",const string & ln = "node",bool ht = false);
		RatePlayer(unsigned int r,const TableTennisPlayer & tp);
		unsigned int Rating () const { return rating; }
		void ResetRating (unsigned int r)  { rating = r; }
};

#endif

