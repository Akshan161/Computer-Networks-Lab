# Experiment 1: Computer Networking Fundamentals & Local File Sharing

---

## Part A: Study of Fundamental Elements of Computer Networking

### 1. Aim
To study the fundamental elements of Computer Networking, including Network Topologies, Transmission Media, Networking Devices, and the RJ-45 connector along with its color coding schemes.

### 2. Theory

#### A. Network Topologies
A network topology defines how computers, cables, and other components are arranged and connected in a network.

1. **Bus Topology**
   - **Description:** All nodes are connected to a single central cable, called the backbone.
   - **Advantages:** Easy to set up and requires minimal cabling.
   - **Disadvantages:** If the central cable fails, the entire network goes down; collision rate increases with additional devices.

2. **Star Topology**
   - **Description:** All devices are individually connected to a central networking device (Hub or Switch).
   - **Advantages:** Easy to troubleshoot and isolate faults; failure of one cable does not affect other devices.
   - **Disadvantages:** If the central hub/switch fails, the whole network becomes unreachable; higher cabling requirement than bus topology.

3. **Ring Topology**
   - **Description:** Each device is connected to two neighboring devices, forming a circular data path.
   - **Advantages:** Equal access to network resources; no packet collisions as data moves unidirectionally (or bidirectionally in dual rings).
   - **Disadvantages:** A single broken connection or failed node disables the entire network ring unless redundant loops exist.

4. **Mesh Topology**
   - **Description:** Every device has a dedicated point-to-point connection to every other device in the network ($N(N-1)/2$ physical links for $N$ nodes in full mesh).
   - **Advantages:** Highly reliable, secure, fault-tolerant, and offers dedicated links with no traffic congestion.
   - **Disadvantages:** High cabling cost, complex installation, and high port usage on hardware.

5. **Tree Topology**
   - **Description:** A hierarchical combination of Star and Bus topologies, organized in parent-child relationships like a tree structure.
   - **Advantages:** Highly scalable and easy to manage in large, departmental organizations.
   - **Disadvantages:** Heavy reliance on the main backbone cable and root nodes.

6. **Hybrid Topology**
   - **Description:** A combination of two or more different standard network topologies (e.g., Star-Ring, Star-Bus).
   - **Advantages:** Flexible and scalable to match specific organizational and layout requirements.
   - **Disadvantages:** Complex design and architecture; higher maintenance and equipment costs.

---

#### B. Transmission Media
Transmission media carry information from a transmitter to a receiver across a network using physical or guided paths.

1. **Coaxial Cable:**
   - Consists of a solid central copper conductor wrapped in dielectric insulation, a braided metal shield, and an outer protective jacket.
   - Moderate bandwidth, resistant to electrical and radio frequency interference.
   - Widely used in cable TV networks, broadband internet access (DOCSIS), and older LAN setups (10BASE2, 10BASE5).

2. **Twisted Pair Cable:**
   - Pairs of insulated copper wires twisted together to cancel out electromagnetic interference (EMI) and crosstalk from adjacent pairs.
   - Available as:
     - **Unshielded Twisted Pair (UTP):** Cost-effective, flexible, standard for corporate LANs (Cat5e, Cat6).
     - **Shielded Twisted Pair (STP):** Encased in foil shielding for high-noise industrial environments.
   - Standard media for Ethernet local area networks (LANs) up to 100 meters.

3. **Optical Fiber Cable:**
   - Made of an ultra-pure glass or plastic core surrounded by cladding with a lower refractive index, transmitting data as pulses of light via Total Internal Reflection (TIR).
   - Immense bandwidth, extremely low attenuation, supports long distances without repeaters, completely immune to EMI/RFI and lightning.
   - Core foundation of Internet backbones, inter-building connections, and high-speed telecom links.

---

#### C. Networking Devices

- **Router:** An intelligent device working at the **Network Layer (Layer 3)** that routes data packets across different networks using logical IP addresses. Maintains dynamic routing tables and connects dissimilar networks (e.g., LAN to WAN/Internet).
- **Hub:** A basic **Physical Layer (Layer 1)** multiport repeater that broadcasts all incoming data packets to every connected port indiscriminately, resulting in high collision domains and shared bandwidth.
- **Switch:** A **Data Link Layer (Layer 2)** device that inspects frame headers and forwards incoming frames directly to the intended destination device using a MAC address lookup table (CAM table), creating separate collision domains per port.
- **Gateway:** A protocol converter acting as a translation bridge between two networks running completely different protocol suites or architectures (e.g., connecting a proprietary enterprise network to the Internet).
- **Modem (Modulator-Demodulator):** Converts digital signals from computers into analog signals for transmission over analog phone/cable lines (modulation), and converts received analog signals back into digital data (demodulation).
- **NIC (Network Interface Card):** A hardware component (PCI/PCIe card or integrated motherboard chip) providing a physical interface and unique hardware MAC address for connecting a computer to a physical or wireless network.

---

#### D. RJ-45 Connector & Color Coding Standards

The **RJ-45 (Registered Jack 45)** is an 8-pin, 8-conductor (8P8C) modular connector used to terminate twisted-pair Ethernet cables (Cat5, Cat5e, Cat6).

##### TIA/EIA-568 Pinout Specifications:

| Pin Number | T568A Standard Wire Color | T568B Standard Wire Color |
| :---: | :--- | :--- |
| **Pin 1** | White / Green | White / Orange |
| **Pin 2** | Green | Orange |
| **Pin 3** | White / Orange | White / Green |
| **Pin 4** | Blue | Blue |
| **Pin 5** | White / Blue | White / Blue |
| **Pin 6** | Orange | Green |
| **Pin 7** | White / Brown | White / Brown |
| **Pin 8** | Brown | Brown |

##### Cable Types:
1. **Straight-Through Cable:** Both ends crimped using the same standard (either T568B to T568B or T568A to T568A). Used to connect heterogeneous devices (e.g., PC to Switch, Switch to Router).
2. **Crossover Cable:** One end wired using T568A and the opposite end wired using T568B. Used to connect similar devices directly without a switch (e.g., PC to PC, Switch to Switch). Modern NICs support Auto-MDI/MDIX, automatically detecting and adjusting pair connections.

---

## Part B: Local File Sharing Within an Organization Using IP Address

### 1. Aim
To configure and establish peer-to-peer and client-server file sharing within a Local Area Network (LAN) using IP addressing and the Server Message Block (SMB) protocol.

### 2. Theory
In a local area network (LAN), host nodes communicate using Internet Protocol (IPv4/IPv6) addresses. File sharing over Windows/Linux environments uses the **Server Message Block (SMB)** protocol over TCP port 445 (or NetBIOS over TCP/IP ports 137–139). SMB allows client software to read, write, open, and lock files on remote hosts just as if they were local disk drives.

### 3. Procedure & Execution Steps

1. **Host Network Identification:**
   Open Command Prompt on the host workstation and inspect network adapter properties:
   ```cmd
   ipconfig /all
   ```
   *Record the IPv4 Address (e.g., `10.17.108.65` or `10.17.106.178`), Subnet Mask (e.g., `255.255.224.0`), and Default Gateway.*

2. **Network Connectivity Verification:**
   From a secondary client workstation on the same subnet, verify low-level ICMP reachability:
   ```cmd
   ping <Host_IP_Address>
   ```
   *Example:*
   ```cmd
   ping 10.17.106.178
   ```
   *Observe 0% packet loss and low Round Trip Time (RTT < 1 ms).*

3. **Folder Creation & Share Configuration:**
   - Create a designated directory on the host (e.g., `C:\Computer Networks Lab`).
   - Right-click the folder $\rightarrow$ **Properties** $\rightarrow$ **Sharing** tab $\rightarrow$ **Advanced Sharing**.
   - Check **Share this folder**, specify a Share Name (e.g., `Computer Networks Lab` or `sit doc`).
   - Click **Permissions** $\rightarrow$ add user group (e.g., `Everyone` or specific domain accounts) $\rightarrow$ grant `Read` and `Change` / `Full Control` permissions $\rightarrow$ Click **Apply** and **OK**.

4. **Accessing the Shared Resource from Remote Client:**
   - On the client machine, open the Windows Run dialog (`Win + R`) or File Explorer address bar.
   - Enter the Universal Naming Convention (UNC) path:
     ```
     \\<Host_IP_Address>\<Share_Name>
     ```
     *Example:*
     ```
     \\10.17.106.178\sit doc
     ```
     *or*
     ```
     \\10.17.108.65\Computer Networks Lab
     ```
   - Provide authentication credentials if prompted, and confirm remote read/write access.

---

### 4. Observation & Verification

| Step | Action Taken | Tool / Command | Observation |
| :---: | :--- | :--- | :--- |
| 1 | Query Host Network Address | `ipconfig` | Host IPv4 address identified on Wi-Fi/Ethernet adapter |
| 2 | Verify Host Reachability | `ping 10.17.106.178` | 4 packets sent, 4 received, 0% loss, TTL=128 |
| 3 | Folder Sharing Setup | Windows Advanced Sharing | Permissions granted for user groups with Read/Write access |
| 4 | Client UNC Connection | `\\10.17.106.178\Shared_Folder` | Shared directory mounted; files created remotely |

---

### 5. Conclusion
Through this experiment:
1. The structural topologies of computer networks, transmission media characteristics (coaxial, twisted-pair, fiber), layer-specific devices (Hub, Switch, Router, Gateway, Modem, NIC), and RJ-45 color coding schemes (T568A / T568B) were comprehensively analyzed.
2. Local area network communication was verified using `ipconfig` and `ping`, and organizational file sharing was successfully configured and validated using SMB over UNC IP paths.

