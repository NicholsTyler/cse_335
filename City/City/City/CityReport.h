/**
 * \file CityReport.h
 *
 * \author Charles B. Owen
 *
 * The city report is generated by the members of the city.
 * It is a collection of objects of type CMemberReport.
 */

#pragma once

#include <memory>
#include <vector>
#include <list>


class CCity;
class CMemberReport;

/**
 * The city report is generated by the members of the city.
 * It is a collection of objects of type CMemberReport.
*/
class CCityReport
{
public:
    CCityReport(CCity* city);

    void Add(std::shared_ptr<CMemberReport> report);

private:
    /// The city this report is for
    CCity* mCity;

protected:
    /**
     * A bin holds some number of member reports
     */
    class Bin {
    public:
        /// A vector of reports stored in this Bin
        std::vector < std::shared_ptr<CMemberReport>> mReports;
    };

    /// The list of Bin objects holding report data.
    std::list<Bin> mBins;

public:
    /** Iterator that iterates over the city reports */
    class Iter
    {
    public:
        /** Constructor
         * \param reports The CityReports instance we're iterating over
         * \param pos The position in the bin of reports
         * \param binIter The position in the list of bins
         */
        Iter(CCityReport* reports, int pos, std::list<Bin>::iterator binIter) : mCollection(reports), mPos(pos), mBinIter(binIter) {}

        /** Test for end of the iterator
         * \param other The iterator to compare with
         * \returns True if the two iterators are not the same */
        bool operator!=(const Iter& other) const
        {
            return (mPos != other.mPos || mBinIter != other.mBinIter);
        }
        
        /** Get value at current position
         * \returns Value at mPos in the collection */
        std::shared_ptr<CMemberReport> operator *() const { return mBinIter->mReports[mPos]; }

        /** Increment the iterator
         * \returns Reference to this iterator */
        const Iter& operator++()
        {
            if (mPos + 1 == mBinIter->mReports.size())
            {
                mBinIter++;
                mPos = 0;
            }
            else
                mPos++;
            return *this;
        }

    private:
        CCityReport *mCollection;              ///< The collection we are iterating over
        int mPos;                              ///< Position in the Bin of Reports
        std::list<Bin>::iterator mBinIter;     ///< Position in the List of Bins
    };

    /** Get an iterator for the beginning of the collection
    * \returns Iter object at position 0 */
    Iter begin() { return Iter(this, 0, mBins.begin()); }

    /** Get an iterator for the end of the collection
     * \returns Iter object at position past the end */
    Iter end() { return Iter(this, 0 , mBins.end()); }
};

