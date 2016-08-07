// Solution to exercism problem: cpp / bob
// http://exercism.io/exercises/cpp/bob/readme
// Copyright (c) 2016 James P. Galasyn
// This project is licensed under the terms of the MIT license.

#pragma once
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;

/// <summary>
/// Contains static methods for talking with Bob, a stereotypical "lackadaisical teenager".
/// </summary>
/// <remarks>
///  Bob answers 'Sure.' if you ask him a question.
///  He answers 'Whoa, chill out!' if you yell at him.
///  He says 'Fine. Be that way!' if you address him without actually saying anything.
///  He answers 'Whatever.' to anything else.
/// </remarks>
class bob
{
public:

    /// <summary>
    /// Tells Bob something. The returned string holds his reply.
    /// </summary>
    /// <param name="tellBob">The phrase to say to Bob.</param>
    /// <returns>Bob's reply.</returns>
    /// <remarks>The <see cref="hey"/> method tests for three kinds of input:
    /// silence, yelling at Bob, and asking Bob a question. These tests are
    /// simple string manipulations without the sophistication of lexical or
    /// semantic analysis. Note that for the <see cref="hey"/> method to work
    /// correctly, the <see cref="IsSilence(string)"/>, <see cref="IsYelling(string)"/>,
    /// and <see cref="IsQuestion(string)"/> methods must be called in this order.
    /// </remarks>
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

    /// <summary>
    /// Determines whether the specified string is equivalent to silence.
    /// </summary>
    /// <param name="tellBob">The string to test for silence.</param>
    /// <returns>true, if <paramref name="tellBob"/> resolves to silence; otherwise, false.</returns>
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

    /// <summary>
    /// Determines whether the specified string is equivalent to yelling.
    /// </summary>
    /// <param name="tellBob">The string to test for silence.</param>
    /// <returns>true, if <paramref name="tellBob"/> resolves to yelling; otherwise, false.</returns>
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

    /// <summary>
    /// Determines whether the specified string is equivalent to asking a question.
    /// </summary>
    /// <param name="tellBob">The string to test for asking a question.</param>
    /// <returns>true, if <paramref name="tellBob"/> resolves to a question; otherwise, false.</returns>
    /// <remarks>Assumes that <paramref name="tellBob"/> has been trimmed and tested for
    /// yelling and being a question.</remarks>
    static bool IsQuestion(const string& tellBob)
    {
        return tellBob.back() == '?';
    }

    /// <summary>
    /// Filters non-alphanumeric characters from the specified string.
    /// </summary>
    /// <param name="str">The string to filter.</param>
    /// <returns>The filtered string.</returns>
    /// <remarks>
    /// Adapted from: How do I remove all non alphanumeric characters from a string except dash?
    /// http://stackoverflow.com/questions/3210393/how-do-i-remove-all-non-alphanumeric-characters-from-a-string-except-dash
    /// </remarks>
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
    static constexpr const char* defaultReply = "Whatever.";
    static constexpr const char* silenceReply = "Fine. Be that way!";
    static constexpr const char* yellingReply = "Whoa, chill out!";
    static constexpr const char* questionReply = "Sure.";
};