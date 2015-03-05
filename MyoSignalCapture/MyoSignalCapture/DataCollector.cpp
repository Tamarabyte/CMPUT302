#include <iostream>
#include <windows.h>
#include <myo/myo.hpp>

using namespace std;

class DataCollector: public myo::DeviceListener {
public:
	DataCollector(): onArm(false), isUnlocked(false), currentPose()
	{
	}

	void onUnpair(myo::Myo * myo, uint64_t timestamp)
	{
		onArm = false;
		isUnlocked = false;
	}

	void onPose(myo::Myo * myo, uint64_t timestamp, myo::Pose pose)
	{
		currentPose = pose;
		if (pose != myo::Pose::unknown && pose != myo::Pose::rest) {
			myo->unlock(myo::Myo::unlockHold);
			cout << pose << endl;
			myo->notifyUserAction();
		} else {
			myo->unlock(myo::Myo::unlockTimed);
		}
	}

	void onArmSync(myo::Myo * myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection)
	{
		onArm = true;
		whichArm = arm;
		if (arm == myo::armLeft) {
			cout << "Left arm you heathen witch. Burn the Witch" << endl;
			myo->notifyUserAction();
			myo->notifyUserAction();
			myo->notifyUserAction();
		}
	}

	void onArmUnsync(myo::Myo * myo, uint64_t timestamp)
	{
		onArm = false;
	}

	void onUnlock(myo::Myo * myo, uint64_t timestamp)
	{
		isUnlocked = true;
		cout << "We're good to go now" << endl;
	}

	void onLock(myo::Myo * myo, uint64_t timestamp)
	{
		isUnlocked = false;
		cout << "No good to go" << endl;
	}

	bool onArm;
	bool isUnlocked;
	myo::Arm whichArm;
	myo::Pose currentPose;

};


int main() {
	try {

		myo::Hub hub("mar.cusist.hegreatest");

		cout << "Connecting... ";

		myo::Myo *myo = hub.waitForMyo(10000);
		if (!myo) {
			throw runtime_error("Unable to find a Myo!");
		}

		cout << "Success" << endl << endl;;
		DataCollector collector;
		hub.addListener(&collector);

		while ( ! GetAsyncKeyState(VK_ESCAPE)) {
			hub.run(10);
		}

		cout << "Press enter to exit" << endl;
		cin.ignore();
		return 0;
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		cerr << "Press enter to continue.";
		cin.ignore();
		return 1;
	}
}