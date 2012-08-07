/*==============================================================================
 
 Copyright (c) 2010, 2011, 2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/


#pragma once

#include <set>

#include "ofMain.h"
#include "ofxVideoSinkInterface.h"

class ofxVideoSinkInterface;

class ofxVideoSourceInterface {
public:
    ofxVideoSourceInterface();
    virtual ~ofxVideoSourceInterface();

    void update();
    
    void sourceFrame(); // push frames
    
    virtual void frameSourced(ofxSharedVideoFrame frame) {};
    
    virtual bool isFrameNew() = 0;
    virtual ofPixelsRef getPixelsRef() = 0;
    
    virtual void close() {};
    virtual void open()  {};
    virtual bool isLoaded() = 0;
        
    bool hasSinks() const;
    bool hasSink(ofxVideoSinkInterface* sink) const;
    
    bool attachToSink(ofxVideoSinkInterface* sink); // sinks call this to be fed by this source
    bool detachFromAllSinks();
    bool detachFromSink(ofxVideoSinkInterface* sink); // sinks call this to be cut off from this source

    void sinkWasAttached(ofxVideoSinkInterface* sink)  {}; // these callbacks are available
    void sinkWasDetatched(ofxVideoSinkInterface* sink) {}; // these callbacks are available
    
    void setOpenOnFirstConnect(bool v);
    void setCloseOnLastDisconnect(bool v);
    
    bool getOpenOnFirstConnect();
    bool getCloseOnLastDisconnect();
 
    set<ofxVideoSinkInterface*> getSinksRef();
    
protected:
    ofxSharedVideoFrame frame;

private:
    
    bool openOnFirstConnection;
    bool closeOnLastDisconnect;
    
    // no subclass access.  all access done via getters 
    // and setters so events will be called
    set<ofxVideoSinkInterface*> sinks;
    set<ofxVideoSinkInterface*>::iterator sinksIter;
};

