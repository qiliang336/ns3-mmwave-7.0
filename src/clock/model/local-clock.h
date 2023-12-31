/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 EPFL
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Guillermo Aguirre <guillermo.aguirrerodrigo@epfl.ch>
 *          Ludovic Thomas <ludovic.thomas@epfl.ch>
 */
#ifndef LOCAL_CLOCK_H
#define LOCAL_CLOCK_H

#include "ns3/object.h"
#include "ns3/object-factory.h"
#include "ns3/clock-model.h"
#include "ns3/scheduler.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/nstime.h"
#include "ns3/system-mutex.h"
#include "ns3/system-thread.h"
namespace ns3 {
/**
 * \file
 * \ingroup Clock
 * ns3::LocalClock declaration
 */
/**
 * \ingroup Clock
 * @brief This class represent the clock interface aggregate to each node. By aggregation, we allow to LocalsimulatorImplementation access to this object
 * through the node.
 * An object of this class has a unique attribute which represent the clock model implementation (ClockModel).
 * This class allow to schedule events in local time and make the conversion between both domains (Local-Global).
 * Also, allows updates of the clock model (SetClock function) by rescheduling events acording to the new clock model. E.i reception of an NTP message with
 * clock parameters update.
 * To this end, the object maintains a list of schedule events in the simulator that need to be update due to the clock update. When
 * a clock update happens, the list is run, removing and rescheduling events with the proper timing.
 */


class LocalClock : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  LocalClock ();
  /**
   * \param ClockModel a implementation of a ClockModel Class.
   */
  LocalClock (Ptr<ClockModel> clock);
  ~LocalClock ();

  /**
   * \brief Return a local time that corresponds to node own clock, different
   * from Simulator::Now().
   * \return Node time
   */
  Time GetLocalTime ();

  /**
   * \brief associate a clock model implementation to the clock of the node.
   * This function is going to be called every time a change on the node clock happens
   * (ie: message update from NTP protocol). This function is going to be in charge of
   * rescheduling the events when there is a change in the clock.
   * \param ClockModel associate to this node.
   */
  void SetClock (Ptr<ClockModel> new_clock_model);

  /**
   * \brief Transform Time from Global (simulator time) to Local(Local Node Time).
   * \param globalTime time
   * \return Local Time
   */
  Time GlobalToLocalTime (Time globalTime);

  /**
   * \brief Transform Time from Local (Local Node Time) to Global (simulator time).
   * \param localTime time
   * \return Global Time
   */
  Time LocalToGlobalTime (Time localTime);

  /**
   * \brief Transform absolute Time from Global (simulator time) to Local (Local Node Time).
   * \param globalDelay time
   * \return  Local Absolute Time
   */
  Time GlobalToLocalDelay (Time globalDelay);

  /**
   * \brief Transform absolute Time from Local (Local Node Time) to Global (simulator time).
   * \param localDelay time
   * \return Global Absolute Time
   */
  Time LocalToGlobalDelay (Time localDelay);

  /**
   * \brief Insert a event in m_events to keep track of the events scheduled by this node.
   * \param event EventId to be inserted
   */
  void InsertEvent (EventId event);
  /**
   * Return true if SetClock function has been called.
   */

private:

  /**
   * \brief ReSchedule an Event in the main simulator. This function calculate the remaining
   * time for the event to be executed and reschedule the event.
   * \param globalTimeStamp globaltime of the vent to be rechedule
   * \param impl Event implementation
   * \param oldClock Clock before the update
   */
  EventId ReSchedule (Time globalTimeStamp, EventImpl *impl, Ptr<ClockModel> oldClock);

  //Clock implementation for the local clock
  Ptr<ClockModel> m_clock;
  typedef std::list<EventId> EventList;
  //List of events schedulled by this node.
  EventList m_events;

};

}// namespace ns3

#endif /* LOCAL_CLOCK_H */
