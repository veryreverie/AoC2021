#include "10.hpp"

namespace Day10{
  std::tuple<long long,long long> day10(const std::vector<std::string>& flines){
    const std::string openers("([{<");
    const std::string closers(")]}>");
    
    std::map<char,char> pairs;
    for (int i=0; i<openers.size(); ++i){
      pairs[openers[i]] = closers[i];
      pairs[closers[i]] = openers[i];
    }
    
    std::map<char,int> corrupt_bracket_scores;
    corrupt_bracket_scores[')'] = 3;
    corrupt_bracket_scores[']'] = 57;
    corrupt_bracket_scores['}'] = 1197;
    corrupt_bracket_scores['>'] = 25137;
    
    std::map<char,int> incomplete_bracket_scores;
    incomplete_bracket_scores['('] = 1;
    incomplete_bracket_scores['['] = 2;
    incomplete_bracket_scores['{'] = 3;
    incomplete_bracket_scores['<'] = 4;
    
    long long total_corrupt_score = 0;
    std::vector<long long> incomplete_scores;
    for (const auto& fline : flines){
      std::vector<char> brackets;
      bool corrupt = false;
      for (const char& c : fline){
        if (Common::item_in_list(c, openers)){
          brackets.push_back(c);
        } else if (brackets.size()>0 and brackets.back()==pairs[c]){
          brackets.pop_back();
        } else {
          corrupt = true;
          total_corrupt_score += corrupt_bracket_scores[c];
          break;
        }
      }
      
      if (not corrupt){
        long long incomplete_score = 0;
        for (auto it = std::crbegin(brackets); it!=std::crend(brackets); ++it){
          incomplete_score *= 5;
          incomplete_score += incomplete_bracket_scores[*it];
        }
        incomplete_scores.push_back(incomplete_score);
      }
    }
    
    std::sort(incomplete_scores.begin(), incomplete_scores.end());
    long long middle_incomplete_score = incomplete_scores[incomplete_scores.size()/2];
    
    return {total_corrupt_score, middle_incomplete_score};
  }
}
