package com.doteyplay.luna.client.container;

import java.net.InetSocketAddress;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.ReentrantLock;

import org.apache.log4j.Logger;
import org.apache.mina.core.future.ConnectFuture;
import org.apache.mina.core.session.IoSession;
import org.apache.mina.transport.socket.SocketConnector;

import com.doteyplay.luna.client.ConnectionInfo;
import com.doteyplay.luna.common.message.DecoderMessage;
import com.doteyplay.luna.common.message.EncoderMessage;
import com.doteyplay.luna.util.SynKeyUtil;

public class SynchronicConnection
{
	
	private static final Logger logger = Logger.getLogger(SynchronicConnection.class);
	
	private IoSession session;
	private ReentrantLock lock;
	public SocketConnector connector;
	private long maxTimeOut;
	private ConnectionInfo connectionInfo;

	private Map<Long, DecoderMessage> resultMap = new ConcurrentHashMap<Long, DecoderMessage>();

	public SynchronicConnection(ConnectionInfo connect)
	{
		lock = new ReentrantLock();
		connectionInfo = connect;
		maxTimeOut = connect.getMaxTimeOut();
	}

	public SynchronicConnection(IoSession session)
	{
		lock = new ReentrantLock();
		this.session = session;
	}

	public void connect()
	{
		ConnectFuture connectFuture = connector.connect(new InetSocketAddress(
				connectionInfo.getServerAddress(), connectionInfo
						.getServerPort()));
		connectFuture.awaitUninterruptibly(connectionInfo.getConnectTime());
		try
		{
			session = connectFuture.getSession();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	public void asynInvoke(EncoderMessage message)
	{
		try
		{
			session.write(message);
		} catch (Exception e)
		{
			e.printStackTrace();
			logger.error("Ŀ��������첽����ʧ��,connectionInfo:"+connectionInfo, e);
		}
	}

	public DecoderMessage synInvoke(EncoderMessage message)
	{
		DecoderMessage result;
		try
		{
			long synKey = SynKeyUtil.getSynkey();
			message.setSynKey(synKey);
			
			session.write(message);
			int temp = 0;
			do
			{
				result = resultMap.remove(synKey);
				if (temp >= maxTimeOut || result != null)
					break;
				temp += 100;
				synchronized (lock)
				{
					lock.wait(100L);
				}
			} while (true);

			return result;
		} catch (Exception e)
		{
			e.printStackTrace();
			logger.error("Ŀ�������ͬ������ʧ��,connectionInfo:"+connectionInfo, e);
		}
		throw new RuntimeException("Ŀ�����û�з���Զ�̵��ý��");
	}

	public void release(DecoderMessage rb)
	{
		resultMap.put(rb.getSynKey(), rb);
		synchronized (lock)
		{
			lock.notify();
		}
	}

	public void close()
	{
		session.close(true);
	}
}