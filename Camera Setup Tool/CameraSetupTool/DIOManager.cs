using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using Automation.BDaq;

namespace CameraSetupTool
{
    public class DIOManager
    {
        public delegate void ErrorOccuranceHandler(string msg);

        /// <summary>
        /// Represents the instance that holds the hardware configuration
        /// </summary>
        private static DIOManager instance;

        /// <summary>
        /// Represents the path of the config file
        /// </summary>
        private const string DIOConfigFilePath = "\\Config\\DIOConfig.xml";

        public DIOConfiguratoion DIOConfig { get; set; }

        public DIOManager()
        {
            this.DIOConfig = new DIOConfiguratoion();
            Initialize();
        }

        public DIOManager(string deviceDescp)
        {
            DeviceInfo = new DeviceInformation(deviceDescp);
            this.DIOConfig = new DIOConfiguratoion();
            Initialize();
        }

        public static DIOManager Current
        {
            get
            {
                if (instance == null)
                {
                    instance = new DIOManager();
                    try
                    {
                        string configFileName = System.Windows.Forms.Application.StartupPath + DIOManager.DIOConfigFilePath;
                        StreamReader reader = new StreamReader(configFileName);
                        XmlSerializer serializer = new XmlSerializer(instance.GetType());
                        instance = serializer.Deserialize(reader) as DIOManager;
                        reader.Close();
                    }
                    catch (System.Exception ex)
                    {
                        System.Windows.Forms.MessageBox.Show("Exception in reading hardware configuration of system\r\n" + ex.Message);
                    }
                }
                return instance;
            }
        }

        private readonly InstantDoCtrl outputDIOControl = new InstantDoCtrl();
        
        private DeviceInformation DeviceInfo;

        public event ErrorOccuranceHandler OnErrorOccured;

        public bool IsInitialized
        {
            get;
            set;
        }

        public bool Initialize()
        {
            try
            {
                if (!IsInitialized)
                {
                    DeviceInfo = new DeviceInformation(this.DIOConfig.DeviceDescription);
                    outputDIOControl.SelectedDevice = DeviceInfo;
                    IsInitialized = outputDIOControl.Initialized;
                }
            }
            catch (Exception e)
            {
                OnErrorOccured("Error initializing device" + e.Message);
                return false;
            }
            return true;
        }

        /// <summary>
        /// Makes the DAC Write Bit high or low
        /// </summary>
        /// <param name="makeHigh">True to make it high, True if data wants to be written </param>
        /// <returns></returns>
        public bool WriteToDataWriteBit(bool makeBitHigh)
        {
            int val = (makeBitHigh) ? 1 : 0;
            ErrorCode err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.DataWriteBit.Port, this.DIOConfig.OutputConfig.DataWriteBit.OutputPin1, Convert.ToByte(val)); 
            if(err == ErrorCode.Success)
            {
                return true;
            }
            return false;
        }


        public bool WriteValueToLight(Lights light, int value)
        {
            ErrorCode err = ErrorCode.Success;
            string valueToBinary = Convert.ToString(value, 2).PadLeft(8,'0');
            char[] valuesOfEachBit = valueToBinary.ToCharArray(); 
            switch (light)
            {
                case Lights.WhiteLight1:
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA0.Port, this.DIOConfig.OutputConfig.SelectionBitA0.OutputPin1, Convert.ToByte(0));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA1.Port, this.DIOConfig.OutputConfig.SelectionBitA1.OutputPin1, Convert.ToByte(0));

                    // Writing Values bit by bit
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin1, Convert.ToByte(valuesOfEachBit[0]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin2, Convert.ToByte(valuesOfEachBit[1]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin3, Convert.ToByte(valuesOfEachBit[2]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin4, Convert.ToByte(valuesOfEachBit[3]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin1, Convert.ToByte(valuesOfEachBit[4]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin2, Convert.ToByte(valuesOfEachBit[5]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin3, Convert.ToByte(valuesOfEachBit[6]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin4, Convert.ToByte(valuesOfEachBit[7]));

                    break;

                case Lights.IRLight1:
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA0.Port, this.DIOConfig.OutputConfig.SelectionBitA0.OutputPin1, Convert.ToByte(0));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA1.Port, this.DIOConfig.OutputConfig.SelectionBitA1.OutputPin1, Convert.ToByte(1));

                    // Writing Values bit by bit
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin1, Convert.ToByte(valuesOfEachBit[0]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin2, Convert.ToByte(valuesOfEachBit[1]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin3, Convert.ToByte(valuesOfEachBit[2]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin4, Convert.ToByte(valuesOfEachBit[3]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin1, Convert.ToByte(valuesOfEachBit[4]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin2, Convert.ToByte(valuesOfEachBit[5]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin3, Convert.ToByte(valuesOfEachBit[6]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin4, Convert.ToByte(valuesOfEachBit[7]));
                    
                    break;

                case Lights.WhiteLight2:
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA0.Port, this.DIOConfig.OutputConfig.SelectionBitA0.OutputPin1, Convert.ToByte(1));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA1.Port, this.DIOConfig.OutputConfig.SelectionBitA1.OutputPin1, Convert.ToByte(0));

                    // Writing Values bit by bit
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin1, Convert.ToByte(valuesOfEachBit[0]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin2, Convert.ToByte(valuesOfEachBit[1]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin3, Convert.ToByte(valuesOfEachBit[2]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin4, Convert.ToByte(valuesOfEachBit[3]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin1, Convert.ToByte(valuesOfEachBit[4]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin2, Convert.ToByte(valuesOfEachBit[5]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin3, Convert.ToByte(valuesOfEachBit[6]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin4, Convert.ToByte(valuesOfEachBit[7]));

                    break;

                case Lights.IRLight2:
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA0.Port, this.DIOConfig.OutputConfig.SelectionBitA0.OutputPin1, Convert.ToByte(1));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.SelectionBitA1.Port, this.DIOConfig.OutputConfig.SelectionBitA1.OutputPin1, Convert.ToByte(1));

                    // Writing Values bit by bit
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin1, Convert.ToByte(valuesOfEachBit[0]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin2, Convert.ToByte(valuesOfEachBit[1]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin3, Convert.ToByte(valuesOfEachBit[2]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit1.Port, this.DIOConfig.OutputConfig.OutputPortBit1.OutputPin4, Convert.ToByte(valuesOfEachBit[3]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin1, Convert.ToByte(valuesOfEachBit[4]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin2, Convert.ToByte(valuesOfEachBit[5]));
                    err = outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin3, Convert.ToByte(valuesOfEachBit[6]));
                    err &= outputDIOControl.WriteBit(this.DIOConfig.OutputConfig.OutputPortBit2.Port, this.DIOConfig.OutputConfig.OutputPortBit2.OutputPin4, Convert.ToByte(valuesOfEachBit[7]));

                    break;
            }

            if (err == ErrorCode.Success)
            {
                return true;
            }
            return false;
        }


    }

    public enum Lights
    {
        WhiteLight1,
        IRLight1,
        WhiteLight2,
        IRLight2

    }

    [Serializable]
    public class DIOConfiguratoion
    {
        public DIOConfiguratoion()
        {
            DeviceDescription = "PCIE-1751,BID#0";
            OutputConfig = new OutputConfiguration();
        }

        /// <summary>
        /// Gets or sets the device description.
        /// </summary>
        /// <value>
        /// The device description.
        /// </value>
        [XmlElement]
        public string DeviceDescription { get; set; }

        /// <summary>
        /// Gets or sets the device ID.
        /// </summary>
        /// <value>
        /// The device ID.
        /// </value>
        [XmlElement]
        public int DeviceID { get; set; }

        /// <summary>
        /// Gets or sets the output configuration.
        /// </summary>
        /// <value>
        /// The output configuration.
        /// </value>
        [XmlElement]
        public OutputConfiguration OutputConfig { get; set; }
    }

    public class DIOPinData
    {
        public DIOPinData()
        { }

        public DIOPinData(int port, int pin)
        {
            Port = port;
            OutputPin1 = pin;
            OutputPin2 = -1;
            OutputPin3 = -1;
            OutputPin4 = -1;
        }

        public DIOPinData(int port, int pin1, int pin2, int pin3, int pin4)
        {
            Port = port;
            OutputPin1 = pin1;
            OutputPin2 = pin2;
            OutputPin3 = pin3;
            OutputPin4 = pin4;
        }

        /// <summary>
        /// Gets or sets the port of the Advantech DIO.
        /// </summary>
        /// <value>
        /// Port Number
        /// </value>
        [XmlAttribute]
        public int Port { get; set; }

        /// <summary>
        /// Gets or sets the pin of the Advantech DIO.
        /// </summary>
        /// <value>
        /// Pin Number
        /// </value>
        [XmlAttribute]
        public int OutputPin1 { get; set; }

        /// <summary>
        /// Gets or sets the pin of the Advantech DIO.
        /// </summary>
        /// <value>
        /// Pin Number
        /// </value>
        [XmlAttribute]
        public int OutputPin2 { get; set; }

        /// <summary>
        /// Gets or sets the pin of the Advantech DIO.
        /// </summary>
        /// <value>
        /// Pin Number
        /// </value>
        [XmlAttribute]
        public int OutputPin3 { get; set; }

        /// <summary>
        /// Gets or sets the pin of the Advantech DIO.
        /// </summary>
        /// <value>
        /// Pin Number
        /// </value>
        [XmlAttribute]
        public int OutputPin4 { get; set; }
    }

    [Serializable]
    public class OutputConfiguration
    {
        public OutputConfiguration()
        {
            DataWriteBit = new DIOPinData(3, 6);
            SelectionBitA0 = new DIOPinData(3, 4);
            SelectionBitA1 = new DIOPinData(3, 5);
            OutputPortBit1 = new DIOPinData(4, 4, 5, 6, 7);
            OutputPortBit2 = new DIOPinData(5, 4, 5, 6, 7);

        }

        public DIOPinData DataWriteBit { get; set; }

        public DIOPinData SelectionBitA0 { get; set; }

        public DIOPinData SelectionBitA1 { get; set; }

        public DIOPinData OutputPortBit1 { get; set; }

        public DIOPinData OutputPortBit2 { get; set; }
    }
}
