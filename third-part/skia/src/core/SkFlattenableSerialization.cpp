/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkFlattenableSerialization.h"

#include "SkData.h"
#include "SkValidatingReadBuffer.h"
#include "SkWriteBuffer.h"

SkData* SkValidatingSerializeFlattenable(SkFlattenable* flattenable) {
    SkWriteBuffer writer(SkWriteBuffer::kValidation_Flag);
    writer.writeFlattenable(flattenable);
    size_t size = writer.bytesWritten();
    SkData* data = SkData::NewUninitialized(size);
    writer.writeToMemory(data->writable_data());
    return data;
}

SkFlattenable* SkValidatingDeserializeFlattenable(const void* data, size_t size,
                                                  SkFlattenable::Type type) {
    SkValidatingReadBuffer buffer(data, size);
    return buffer.readFlattenable(type);
}
