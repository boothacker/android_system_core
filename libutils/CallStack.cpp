/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "CallStack"

#include <utils/CallStack.h>
#include <utils/Printer.h>
#include <utils/Errors.h>
#include <utils/Log.h>
#include <UniquePtr.h>

#include <backtrace/Backtrace.h>

namespace android {

CallStack::CallStack() {
}

CallStack::CallStack(const char* logtag, int32_t ignoreDepth) {
    this->update(ignoreDepth+1);
    this->log(logtag);
}

CallStack::~CallStack() {
}

void CallStack::update(int32_t ignoreDepth, pid_t tid) {
    mFrameLines.clear();

    UniquePtr<Backtrace> backtrace(Backtrace::Create(BACKTRACE_CURRENT_PROCESS, tid));
    if (!backtrace->Unwind(ignoreDepth)) {
        ALOGW("%s: Failed to unwind callstack.", __FUNCTION__);
    }
    for (size_t i = 0; i < backtrace->NumFrames(); i++) {
      mFrameLines.push_back(String8(backtrace->FormatFrameData(i).c_str()));
    }
}

void CallStack::log(const char* logtag, android_LogPriority priority, const char* prefix) const {
    LogPrinter printer(logtag, priority, prefix, /*ignoreBlankLines*/false);
    print(printer);
}

/*#ifdef MTK_MT6589
void CallStack::update(int32_t ignoreDepth, int32_t maxDepth) {
    update(ignoreDepth, maxDepth, CURRENT_THREAD);
}

void CallStack::dump(const char* prefix) const {
    backtrace_symbol_t symbols[mCount];

    get_backtrace_symbols(mStack, mCount, symbols);
    for (size_t i = 0; i < mCount; i++) {
        char line[MAX_BACKTRACE_LINE_LENGTH];
        format_backtrace_line(i, &mStack[i], &symbols[i],
                line, MAX_BACKTRACE_LINE_LENGTH);
        ALOGD("%s%s", prefix, line);
    }
    free_backtrace_symbols(symbols, mCount);
}
#endif*/

void CallStack::dump(int fd, int indent, const char* prefix) const {
    FdPrinter printer(fd, indent, prefix);
    print(printer);
}

String8 CallStack::toString(const char* prefix) const {
    String8 str;

    String8Printer printer(&str, prefix);
    print(printer);

    return str;
}

void CallStack::print(Printer& printer) const {
    for (size_t i = 0; i < mFrameLines.size(); i++) {
        printer.printLine(mFrameLines[i]);
    }
}

#ifdef MTK_MT6589
CallStac2::CallStac2() :
         mCount(0) {
 }
 
 CallStac2::CallStac2(const CallStac2& rhs) :
         mCount(rhs.mCount) {
     if (mCount) {
         memcpy(mStack, rhs.mStack, mCount * sizeof(backtrace_frame_t));
     }
 }
 
 CallStac2::~CallStac2() {
 }
 
 CallStac2& CallStac2::operator = (const CallStac2& rhs) {
     mCount = rhs.mCount;
     if (mCount) {
         memcpy(mStack, rhs.mStack, mCount * sizeof(backtrace_frame_t));
     }
     return *this;
 }
 
 bool CallStac2::operator == (const CallStac2& rhs) const {
     if (mCount != rhs.mCount)
         return false;
     return !mCount || memcmp(mStack, rhs.mStack, mCount * sizeof(backtrace_frame_t)) == 0;
 }
 
 bool CallStac2::operator != (const CallStac2& rhs) const {
     return !operator == (rhs);
 }
 
 bool CallStac2::operator < (const CallStac2& rhs) const {
     if (mCount != rhs.mCount)
         return mCount < rhs.mCount;
     return memcmp(mStack, rhs.mStack, mCount * sizeof(backtrace_frame_t)) < 0;
 }
 
 bool CallStac2::operator >= (const CallStac2& rhs) const {
     return !operator < (rhs);
 }
 
 bool CallStac2::operator > (const CallStac2& rhs) const {
     if (mCount != rhs.mCount)
         return mCount > rhs.mCount;
     return memcmp(mStack, rhs.mStack, mCount * sizeof(backtrace_frame_t)) > 0;
 }
 
 bool CallStac2::operator <= (const CallStac2& rhs) const {
     return !operator > (rhs);
 }
 
 const void* CallStac2::operator [] (int index) const {
     if (index >= int(mCount))
         return 0;
     return reinterpret_cast<const void*>(mStack[index].absolute_pc);
 }
 
 void CallStac2::clear() {
     mCount = 0;
 }
 
 void CallStac2::update(int32_t ignoreDepth, int32_t maxDepth) {
     if (maxDepth > MAX_DEPTH) {
         maxDepth = MAX_DEPTH;
     }
     ssize_t count = unwind_backtrace(mStack, ignoreDepth + 1, maxDepth);
     mCount = count > 0 ? count : 0;
 }
 
 void CallStac2::dump(const char* prefix) const {
     backtrace_symbol_t symbols[mCount];
 
     get_backtrace_symbols(mStack, mCount, symbols);
     for (size_t i = 0; i < mCount; i++) {
         char line[MAX_BACKTRACE_LINE_LENGTH];
         format_backtrace_line(i, &mStack[i], &symbols[i],
                 line, MAX_BACKTRACE_LINE_LENGTH);
         ALOGD("%s%s", prefix, line);
     }
     free_backtrace_symbols(symbols, mCount);
 }
 
 String8 CallStac2::toString(const char* prefix) const {
     String8 str;
     backtrace_symbol_t symbols[mCount];
 
     get_backtrace_symbols(mStack, mCount, symbols);
     for (size_t i = 0; i < mCount; i++) {
         char line[MAX_BACKTRACE_LINE_LENGTH];
         format_backtrace_line(i, &mStack[i], &symbols[i],
                 line, MAX_BACKTRACE_LINE_LENGTH);
         str.append(prefix);
         str.append(line);
         str.append("\n");
     }
     free_backtrace_symbols(symbols, mCount);
     return str;
 }
#endif
 
}; // namespace android
