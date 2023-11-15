package com.bignerdranch.android.criminalintent;


import java.util.Date;
import java.util.UUID;


public class Crime {
    private UUID mId;
    private String mTitle;
    private Date mData;
    private boolean mIsSolved;

    public Crime() {
        mId = UUID.randomUUID();
        mData = new Date();
    }

    public UUID getId() {
        return mId;
    }

    public String getTitle() {
        return mTitle;
    }

    public void setTitle(String title) {
        mTitle = title;
    }

    public Date getData() {
        return mData;
    }

    public void setData(Date data) {
        mData = data;
    }

    public boolean isSolved() {
        return mIsSolved;
    }

    public void setSolved(boolean solved) {
        mIsSolved = solved;
    }
}
