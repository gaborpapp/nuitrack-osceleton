//
// file SkeletonTracker.cpp
// Created by Bartosz Sobol
//


#include "SkeletonTracker.h"

namespace osceleton {

    SkeletonTracker::SkeletonTracker() {
        tdv::nuitrack::Nuitrack::init();
        depth_sensor_ = tdv::nuitrack::DepthSensor::create();
        skeleton_tracker_ = tdv::nuitrack::SkeletonTracker::create();
        user_tracker_ = tdv::nuitrack::UserTracker::create();
        tdv::nuitrack::Nuitrack::run();
    }

    SkeletonTracker::SkeletonTracker(const bool mirror) : SkeletonTracker{} {
        depth_sensor_->setMirror(mirror);
    }

    SkeletonTracker::~SkeletonTracker() {
        SkeletonTracker::release_nuitrack();
    }

    void SkeletonTracker::update() {
        tdv::nuitrack::Nuitrack::waitUpdate(skeleton_tracker_);
        skeleton_data_ = skeleton_tracker_->getSkeletons();
    }

    std::vector<tdv::nuitrack::Skeleton> SkeletonTracker::getSkeletons() const {
        return skeleton_data_->getSkeletons();
    }

    void SkeletonTracker::release_nuitrack() {
        tdv::nuitrack::Nuitrack::release();
    }

    void SkeletonTracker::registerOnNewUserCallback(const tdv::nuitrack::UserTracker::OnNewUser &callback) {
        user_tracker_->connectOnNewUser(callback);
    }

    void SkeletonTracker::registerOnLostUserCallback(const tdv::nuitrack::UserTracker::OnLostUser &callback) {
        user_tracker_->connectOnLostUser(callback);
    }

}


#include "SkeletonTracker.h"
