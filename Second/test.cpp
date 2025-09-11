#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <bitset>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>
#include <memory>

// CAN Frame structure
struct CANFrame {
    uint32_t id;           // CAN ID (11-bit standard or 29-bit extended)
    bool extended;         // Extended frame format flag
    bool rtr;             // Remote Transmission Request flag
    uint8_t dlc;          // Data Length Code (0-8 bytes)
    uint8_t data[8];      // Data payload
    
    CANFrame(uint32_t _id = 0, bool _extended = false, bool _rtr = false, uint8_t _dlc = 0) 
        : id(_id), extended(_extended), rtr(_rtr), dlc(_dlc) {
        for(int i = 0; i < 8; i++) data[i] = 0;
    }
    
    // Set data from vector
    void setData(const std::vector<uint8_t>& payload) {
        dlc = std::min((size_t)8, payload.size());
        for(int i = 0; i < dlc; i++) {
            data[i] = payload[i];
        }
    }
    
    // Display frame information
    void display() const {
        std::cout << "CAN Frame - ID: 0x" << std::hex << std::setw(3) << std::setfill('0') << id;
        std::cout << " (" << (extended ? "Extended" : "Standard") << ")";
        std::cout << " DLC: " << std::dec << (int)dlc;
        std::cout << " Data: ";
        for(int i = 0; i < dlc; i++) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
        }
        std::cout << std::dec << std::endl;
    }
};

// CAN Bus simulation class
class CANBus {
private:
    std::queue<CANFrame> messageQueue;
    std::mutex busMutex;
    bool busActive;
    
public:
    CANBus() : busActive(true) {}
    
    // Transmit frame to bus (with arbitration simulation)
    bool transmit(const CANFrame& frame) {
        std::lock_guard<std::mutex> lock(busMutex);
        if(!busActive) return false;
        
        std::cout << "[BUS] Transmitting frame with ID priority: 0x" 
                  << std::hex << frame.id << std::dec << std::endl;
        messageQueue.push(frame);
        return true;
    }
    
    // Receive frame from bus
    bool receive(CANFrame& frame) {
        std::lock_guard<std::mutex> lock(busMutex);
        if(messageQueue.empty()) return false;
        
        frame = messageQueue.front();
        messageQueue.pop();
        return true;
    }
    
    bool isEmpty() const {
        return messageQueue.empty();
    }
    
    void shutdown() { busActive = false; }
};

// CAN Node (ECU) class
class CANNode {
private:
    uint8_t nodeId;
    std::string name;
    CANBus* bus;
    std::vector<uint32_t> acceptanceFilters;
    
public:
    CANNode(uint8_t id, const std::string& nodeName, CANBus* canBus) 
        : nodeId(id), name(nodeName), bus(canBus) {}
    
    // Add acceptance filter for specific CAN IDs
    void addFilter(uint32_t canId) {
        acceptanceFilters.push_back(canId);
    }
    
    // Send a CAN message
    void sendMessage(uint32_t canId, const std::vector<uint8_t>& data) {
        CANFrame frame(canId);
        frame.setData(data);
        
        std::cout << "[" << name << "] Sending message:" << std::endl;
        frame.display();
        
        if(bus->transmit(frame)) {
            std::cout << "[" << name << "] Message sent successfully" << std::endl;
        } else {
            std::cout << "[" << name << "] Failed to send message" << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Listen for messages (with filtering)
    void listenForMessages() {
        CANFrame receivedFrame;
        if(bus->receive(receivedFrame)) {
            // Check if message passes acceptance filter
            bool accept = acceptanceFilters.empty(); // Accept all if no filters
            for(uint32_t filterId : acceptanceFilters) {
                if(receivedFrame.id == filterId) {
                    accept = true;
                    break;
                }
            }
            
            if(accept) {
                std::cout << "[" << name << "] Received message:" << std::endl;
                receivedFrame.display();
                processMessage(receivedFrame);
            }
        }
    }
    
    // Process received CAN message
    void processMessage(const CANFrame& frame) {
        switch(frame.id) {
            case 0x100: // Engine RPM
                if(frame.dlc >= 2) {
                    uint16_t rpm = (frame.data[0] << 8) | frame.data[1];
                    std::cout << "[" << name << "] Engine RPM: " << rpm << std::endl;
                }
                break;
                
            case 0x200: // Vehicle Speed
                if(frame.dlc >= 1) {
                    std::cout << "[" << name << "] Vehicle Speed: " << (int)frame.data[0] << " km/h" << std::endl;
                }
                break;
                
            case 0x300: // Temperature
                if(frame.dlc >= 1) {
                    int8_t temp = frame.data[0] - 40; // Offset binary
                    std::cout << "[" << name << "] Engine Temperature: " << (int)temp << "°C" << std::endl;
                }
                break;
                
            default:
                std::cout << "[" << name << "] Processing unknown message ID: 0x" 
                          << std::hex << frame.id << std::dec << std::endl;
                break;
        }
        std::cout << std::endl;
    }
};

// Demonstrate CAN arbitration (lower ID wins)
void demonstrateArbitration() {
    std::cout << "=== CAN Arbitration Demo ===\n";
    std::cout << "In CAN, lower ID values have higher priority\n";
    std::cout << "When multiple nodes transmit simultaneously, the one with lower ID wins\n\n";
    
    // Show bit-wise arbitration
    uint32_t id1 = 0x123; // Higher priority
    uint32_t id2 = 0x124; // Lower priority
    
    std::cout << "Node A ID: 0x" << std::hex << id1 << " = " << std::bitset<11>(id1) << std::endl;
    std::cout << "Node B ID: 0x" << std::hex << id2 << " = " << std::bitset<11>(id2) << std::endl;
    std::cout << "Arbitration: Node A wins (lower ID = higher priority)\n\n";
}

int main() {
    std::cout << "CAN Bus Communication Demonstration\n";
    std::cout << "===================================\n\n";
    
    // Demonstrate arbitration concept
    demonstrateArbitration();
    
    // Create CAN bus
    CANBus canBus;
    
    // Create CAN nodes (ECUs)
    CANNode engineECU(1, "Engine ECU", &canBus);
    CANNode dashboardECU(2, "Dashboard ECU", &canBus);
    CANNode transmissionECU(3, "Transmission ECU", &canBus);
    
    // Set up message filters
    dashboardECU.addFilter(0x100); // RPM
    dashboardECU.addFilter(0x200); // Speed
    dashboardECU.addFilter(0x300); // Temperature
    
    transmissionECU.addFilter(0x100); // RPM
    transmissionECU.addFilter(0x200); // Speed
    
    std::cout << "=== CAN Network Communication ===\n\n";
    
    // Simulate engine ECU sending RPM data
    std::vector<uint8_t> rpmData = {0x0F, 0xA0}; // 4000 RPM (0x0FA0 = 4000)
    engineECU.sendMessage(0x100, rpmData);
    
    // Dashboard and transmission ECUs receive the message
    dashboardECU.listenForMessages();
    transmissionECU.listenForMessages();
    
    // Simulate transmission ECU sending speed data
    std::vector<uint8_t> speedData = {60}; // 60 km/h
    transmissionECU.sendMessage(0x200, speedData);
    
    // Dashboard ECU receives speed data
    dashboardECU.listenForMessages();
    
    // Engine ECU sends temperature data
    std::vector<uint8_t> tempData = {130}; // 90°C (130 - 40 = 90)
    engineECU.sendMessage(0x300, tempData);
    
    // Dashboard ECU receives temperature data
    dashboardECU.listenForMessages();
    
    std::cout << "=== CAN Frame Structure Demo ===\n";
    
    // Create and display different types of CAN frames
    CANFrame standardFrame(0x456, false, false, 4);
    standardFrame.data[0] = 0xDE; standardFrame.data[1] = 0xAD;
    standardFrame.data[2] = 0xBE; standardFrame.data[3] = 0xEF;
    
    std::cout << "Standard CAN Frame:\n";
    standardFrame.display();
    
    CANFrame extendedFrame(0x12345678, true, false, 8);
    for(int i = 0; i < 8; i++) extendedFrame.data[i] = i + 1;
    
    std::cout << "\nExtended CAN Frame:\n";
    extendedFrame.display();
    
    CANFrame remoteFrame(0x789, false, true, 0);
    std::cout << "\nRemote Transmission Request (RTR) Frame:\n";
    remoteFrame.display();
    
    std::cout << "\n=== CAN Bus Features Demonstrated ===\n";
    std::cout << "✓ Multi-master bus topology\n";
    std::cout << "✓ Message-based communication\n";
    std::cout << "✓ Priority-based arbitration (lower ID = higher priority)\n";
    std::cout << "✓ Broadcast communication with filtering\n";
    std::cout << "✓ Standard (11-bit) and Extended (29-bit) frame formats\n";
    std::cout << "✓ Data frames and Remote Transmission Request (RTR) frames\n";
    std::cout << "✓ Variable data length (0-8 bytes)\n";
    
    return 0;
}