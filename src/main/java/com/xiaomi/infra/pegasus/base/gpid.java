// Copyright (c) 2017, Xiaomi, Inc.  All rights reserved.
// This source code is licensed under the Apache License Version 2.0, which
// can be found in the LICENSE file in the root directory of this source tree.
/**
 * Autogenerated by Thrift
 *
 * <p>DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
package com.xiaomi.infra.pegasus.base;

import com.xiaomi.infra.pegasus.thrift.*;
import com.xiaomi.infra.pegasus.thrift.async.*;
import com.xiaomi.infra.pegasus.thrift.meta_data.*;
import com.xiaomi.infra.pegasus.thrift.protocol.*;
import com.xiaomi.infra.pegasus.thrift.transport.*;
import java.util.Collections;
import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.Map;

public class gpid implements TBase<gpid, gpid._Fields>, java.io.Serializable, Cloneable {
  private static final TStruct STRUCT_DESC = new TStruct("gpid");

  // well, the higher 32-bit is pidx, the lower 32-bit app-id
  public long value;

  /**
   * The set of fields this struct contains, along with convenience methods for finding and
   * manipulating them.
   */
  public enum _Fields implements TFieldIdEnum {
    ;

    private static final Map<String, _Fields> byName = new HashMap<String, _Fields>();

    static {
      for (_Fields field : EnumSet.allOf(_Fields.class)) {
        byName.put(field.getFieldName(), field);
      }
    }

    /** Find the _Fields constant that matches fieldId, or null if its not found. */
    public static _Fields findByThriftId(int fieldId) {
      switch (fieldId) {
        default:
          return null;
      }
    }

    /** Find the _Fields constant that matches fieldId, throwing an exception if it is not found. */
    public static _Fields findByThriftIdOrThrow(int fieldId) {
      _Fields fields = findByThriftId(fieldId);
      if (fields == null)
        throw new IllegalArgumentException("Field " + fieldId + " doesn't exist!");
      return fields;
    }

    /** Find the _Fields constant that matches name, or null if its not found. */
    public static _Fields findByName(String name) {
      return byName.get(name);
    }

    private final short _thriftId;
    private final String _fieldName;

    _Fields(short thriftId, String fieldName) {
      _thriftId = thriftId;
      _fieldName = fieldName;
    }

    public short getThriftFieldId() {
      return _thriftId;
    }

    public String getFieldName() {
      return _fieldName;
    }
  }

  public static final Map<_Fields, FieldMetaData> metaDataMap;

  static {
    Map<_Fields, FieldMetaData> tmpMap = new EnumMap<_Fields, FieldMetaData>(_Fields.class);
    metaDataMap = Collections.unmodifiableMap(tmpMap);
    FieldMetaData.addStructMetaDataMap(gpid.class, metaDataMap);
  }

  public gpid() {
    value = 0;
  }

  public gpid(int app_id, int pidx) {
    value = (((long) pidx) << 32) + app_id;
  }

  public int get_app_id() {
    return (int) (value & 0x00000000ffffffffl);
  }

  public int get_pidx() {
    return (int) (value >>> 32);
  }

  public void set_pidx(int pidx) {
    value = (((long) pidx) << 32) + (value & 0x00000000ffffffffl);
  }

  public void set_app_id(int appid) {
    value = (value & 0xffffffff00000000l) + appid;
  }
  /** Performs a deep copy on <i>other</i>. */
  public gpid(gpid other) {
    value = other.value;
  }

  public gpid deepCopy() {
    return new gpid(this);
  }

  @Override
  public void clear() {
    value = 0;
  }

  public void setFieldValue(_Fields field, Object value) {
    switch (field) {
    }
  }

  public Object getFieldValue(_Fields field) {
    switch (field) {
    }
    throw new IllegalStateException();
  }

  /**
   * Returns true if field corresponding to fieldID is set (has been asigned a value) and false
   * otherwise
   */
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new IllegalArgumentException();
    }

    switch (field) {
    }
    throw new IllegalStateException();
  }

  @Override
  public boolean equals(Object that) {
    if (that == null) return false;
    if (that instanceof gpid) return this.equals((gpid) that);
    return false;
  }

  public boolean equals(gpid that) {
    if (that == null) return false;
    return value == that.value;
  }

  @Override
  public int hashCode() {
    return get_app_id() ^ get_pidx();
  }

  public long gpid_hash() {
    long result = get_app_id();
    return (result << 32) + get_pidx();
  }

  public int compareTo(gpid other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }
    if (value < other.value) return -1;
    return value > other.value ? 1 : 0;
  }

  public _Fields fieldForId(int fieldId) {
    return _Fields.findByThriftId(fieldId);
  }

  public void read(TProtocol iprot) throws TException {
    value = iprot.readI64();
    // check for required fields of primitive type, which can't be checked in the validate method
    validate();
  }

  public void write(TProtocol oprot) throws TException {
    oprot.writeI64(value);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder("gpid(");
    sb.append(get_app_id());
    sb.append(".");
    sb.append(get_pidx());
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws TException {
    // check for required fields
  }
}
