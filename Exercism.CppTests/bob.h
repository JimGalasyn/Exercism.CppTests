#pragma once
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;

class bob
{
public:
    static string bob::hey(string tellBob)
    {
        // Initialize the return value to the default reply.
        string retval = bob::defaultReply;

        // Trim leading and trailing whitespace.
        string tellBobTrimmed = boost::trim_copy<string>(tellBob);

        // Test the trimmed string for the three input types.
        // These calls are order-dependent.
        if (IsSilence(tellBobTrimmed))
        {
            retval = bob::silenceReply;
        }
        else if (IsYelling(tellBobTrimmed))
        {
            retval = bob::yellingReply;
        }
        else if (IsQuestion(tellBobTrimmed))
        {
            retval = bob::questionReply;
        }

        return retval;
    }

private:
    static bool IsSilence(const string& tellBob)
    {
        bool isSilence = tellBob.empty();

        if (!isSilence)
        {
            isSilence = 
                (tellBob.size() == 1) && 
                (isalnum(tellBob[0]) == 1);
        }

        return isSilence;
    }

    static bool IsYelling(string tellBob)
    {
        bool isYelling = false;

        string scrubbed = FilterNonAlpha(tellBob);
        if (!IsSilence(scrubbed))
        {
            string tellBobUppercase = boost::to_upper_copy<string>(tellBob);
            isYelling = (tellBobUppercase == tellBob);
        }

        return isYelling;
    }

    static bool IsQuestion(const string& tellBob)
    {
        return tellBob.back() == '?';  //.end(); //.EndsWith("?");
    }

    static string FilterNonAlpha(const string& str)
    {
        string retval;

        const int sz = str.size();

        for (int i = 0; i < sz; i++)
        {
            if (isalpha(str[i]))
            {
                retval.push_back(i);
            }
        }

        return retval;
    }

    // String constants.
    //static constexpr const char* STRING = "some useful string constant";
    static constexpr const char* defaultReply = "Whatever.";
    static constexpr const char* silenceReply = "Fine. Be that way!";
    static constexpr const char* yellingReply = "Whoa, chill out!";
    static constexpr const char* questionReply = "Sure.";

    /*static const string defaultReply = "Whatever.";
    const string silenceReply = "Fine. Be that way!";
    const string yellingReply = "Whoa, chill out!";
    const string questionReply = "Sure.";*/
};